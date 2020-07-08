/**********************************************************************

  fft.cpp


  This class is a C++ wrapper for original code
  written by Dominic Mazzoni in September 2000

  This file contains a few FFT routines, including a real-FFT
  routine that is almost twice as fast as a normal complex FFT,
  and a power spectrum routine which is more convenient when
  you know you don't care about phase information.  It now also
  contains a few basic windowing functions.

  Some of this code was based on a free implementation of an FFT
  by Don Cross, available on the web at:

http://www.intersrv.com/~dcross/fft.html

The basic algorithm for his code was based on Numerical Recipes
in Fortran.  I optimized his code further by reducing array
accesses, caching the bit reversal table, and eliminating
float-to-double conversions, and I added the routines to
calculate a real FFT and a real power spectrum.

Note: all of these routines use single-precision floats.
I have found that in practice, floats work well until you
get above 8192 samples.  If you need to do a larger FFT,
you need to use doubles.

 **********************************************************************/

#include "fft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <cstring>

int **gFFTBitTable = NULL;
const int MaxFastBits = 16;
const double angle_numerator = 2.0 * M_PI;


struct FftLookup
{
    unsigned block_size;
    double delta_angle;
    float sm2;
    float sm1;
    float cm2;
    float cm1;
    float w;
};


std::vector<FftLookup> lookup;

inline const FftLookup& getLookupValue(unsigned const shift)
{
    for (unsigned i = lookup.size(); i <= shift; ++i) {
        FftLookup fft_lo;
        fft_lo.block_size = 2 << i;
        fft_lo.delta_angle = angle_numerator / (double) fft_lo.block_size;

        fft_lo.sm2 = sin(-2 * fft_lo.delta_angle);
        fft_lo.sm1 = sin(-fft_lo.delta_angle);
        fft_lo.cm2 = cos(-2 * fft_lo.delta_angle);
        fft_lo.cm1 = cos(-fft_lo.delta_angle);
        fft_lo.w = 2 * fft_lo.cm1;
        lookup.push_back(fft_lo);
    }
    return lookup[shift];
}


inline int IsPowerOfTwo(int x)
{
    if (x < 2)
        return false;

    if (x & (x - 1))             /* Thanks to 'byang' for this cute trick! */
        return false;

    return true;
}

inline int NumberOfBitsNeeded(int PowerOfTwo)
{
    int i;

#ifdef DEBUG
    if (PowerOfTwo < 2) {
        fprintf(stderr, "Error: FFT called with size %d\n", PowerOfTwo);
        exit(1);
    }
#endif

    for (i = 0;; i++)
        if (PowerOfTwo & (1 << i))
            return i;
}

inline int ReverseBits(int index, int NumBits)
{
    int i, rev;

    for (i = rev = 0; i < NumBits; i++) {
        rev = (rev << 1) | (index & 1);
        index >>= 1;
    }

    return rev;
}

void InitFFT()
{
    gFFTBitTable = new int *[MaxFastBits];

    int len = 2;
    for (int b = 1; b <= MaxFastBits; b++) {

        gFFTBitTable[b - 1] = new int[len];

        for (int i = 0; i < len; i++)
            gFFTBitTable[b - 1][i] = ReverseBits(i, b);

        len <<= 1;
    }
}

inline int FastReverseBits(int i, int NumBits)
{
    if (NumBits <= MaxFastBits)
        return gFFTBitTable[NumBits - 1][i];
    else
        return ReverseBits(i, NumBits);
}

/*
 * Complex Fast Fourier Transform
 */

void FFT(int NumSamples,
         float* RealIn,
         float* ImagIn,
         float* RealOut,
         float* ImagOut)
{
    int NumBits;                 /* Number of bits needed to store indices */
    int i, j, k, n;
    int BlockSize, BlockEnd;

    float tr, ti;                /* temp real, temp imaginary */

    /*
       if (!IsPowerOfTwo(NumSamples)) {
       fprintf(stderr, "%d is not a power of two\n", NumSamples);
       exit(1);
       }
       */

    if (!gFFTBitTable)
        InitFFT();

    NumBits = NumberOfBitsNeeded(NumSamples);

    /*
     **   Do simultaneous data copy and bit-reversal ordering into outputs...
     */

    for (i = 0; i < NumSamples; i++) {
        j = FastReverseBits(i, NumBits);
        RealOut[j] = RealIn[i];
        ImagOut[j] = ImagIn[i];
    }

    /*
     **   Do the FFT itself...
     */

    BlockEnd = 1;
    BlockSize = 2;
    for (int shift = 0;; ++shift) {
        const FftLookup& fft_lo = getLookupValue(shift);
        BlockSize = fft_lo.block_size;
        if (BlockSize > NumSamples) {
            return;
        }


        float ar0, ar1, ar2, ai0, ai1, ai2;

        for (i = 0; i < NumSamples; i += BlockSize) {
            ar2 = fft_lo.cm2;
            ar1 = fft_lo.cm1;

            ai2 = fft_lo.sm2;
            ai1 = fft_lo.sm1;

            for (j = i, n = 0; n < BlockEnd; j++, n++) {
                ar0 = fft_lo.w * ar1 - ar2;
                ar2 = ar1;
                ar1 = ar0;

                ai0 = fft_lo.w * ai1 - ai2;
                ai2 = ai1;
                ai1 = ai0;

                k = j + BlockEnd;
                tr = ar0 * RealOut[k] - ai0 * ImagOut[k];
                ti = ar0 * ImagOut[k] + ai0 * RealOut[k];

                RealOut[k] = RealOut[j] - tr;
                ImagOut[k] = ImagOut[j] - ti;

                RealOut[j] += tr;
                ImagOut[j] += ti;
            }
        }

        BlockEnd = BlockSize;
    }

}

/*
 * Real Fast Fourier Transform
 *
 * This function was based on the code in Numerical Recipes in C.
 * In Num. Rec., the inner loop is based on a single 1-based array
 * of interleaved real and imaginary numbers.  Because we have two
 * separate zero-based arrays, our indices are quite different.
 * Here is the correspondence between Num. Rec. indices and our indices:
 *
 * i1  <->  real[i]
 * i2  <->  imag[i]
 * i3  <->  real[n/2-i]
 * i4  <->  imag[n/2-i]
 */
void RealFFT(int NumSamples,
             float* RealIn,
             float* RealOut,
             float* ImagOut)
{
    static const int Half = NumSamples / 2;

    static const float theta = M_PI / Half;
    static const float wtemp_start = float (sin(0.5 * theta));

    static const float wpr = -2.0 * wtemp_start * wtemp_start;
    static const float wpi = float (sin(theta));

    float tmpReal[Half];
    float tmpImag[Half];

    for (unsigned i = 0; i < Half; i++) {
        tmpReal[i] = RealIn[2 * i];
        tmpImag[i] = RealIn[2 * i + 1];
    }

    FFT(Half, tmpReal, tmpImag, RealOut, ImagOut);

    float wtemp = wtemp_start;
    float wr = 1.0 + wpr;
    float wi = wpi;

    int i3;

    float h1r, h1i, h2r, h2i;

    for (unsigned i = 1; i < Half / 2; i++) {

        i3 = Half - i;

        h1r = 0.5 * (RealOut[i] + RealOut[i3]);
        h1i = 0.5 * (ImagOut[i] - ImagOut[i3]);
        h2r = 0.5 * (ImagOut[i] + ImagOut[i3]);
        h2i = -0.5 * (RealOut[i] - RealOut[i3]);

        RealOut[i] = h1r + wr * h2r - wi * h2i;
        ImagOut[i] = h1i + wr * h2i + wi * h2r;
        RealOut[i3] = h1r - wr * h2r + wi * h2i;
        ImagOut[i3] = -h1i + wr * h2i + wi * h2r;

        wr = (wtemp = wr) * wpr - wi * wpi + wr;
        wi = wi * wpr + wtemp * wpi + wi;
    }

    RealOut[0] = (h1r = RealOut[0]) + ImagOut[0];
    ImagOut[0] = h1r - ImagOut[0];
}


/*
 * Windowing Functions
 */
std::vector<float> window_coeff;

void WindowFunc(int NumSamples, float* in)
{
    if (NumSamples != window_coeff.size()) {
        window_coeff.resize(NumSamples);
        // Hanning
        for (unsigned i = 0; i < NumSamples; i++)
            window_coeff[i] = 0.50 - 0.50 * cos(2 * M_PI * i / (NumSamples - 1));
    }

    for (unsigned i = 0; i < NumSamples; i++)
        in[i] *= window_coeff[i];

}

/* constructor */
fft::fft() {
}

/* destructor */
fft::~fft() {
}

/* Calculate the power spectrum */
void fft::powerSpectrum(int start, int half, const float * const data, int windowSize,float *magnitude,float *phase, float *power, float *avg_power) {
    float total_power = 0.0f;

    /* processing variables*/
    float in_real [windowSize];
    float in_img  [windowSize];
    float out_real[windowSize];
    float out_img [windowSize];

    memcpy(&in_real[0], &data[start], sizeof(float) * windowSize);

    WindowFunc(windowSize, in_real);
    RealFFT(windowSize, in_real, out_real, out_img);

    for (unsigned i = 0; i < half; i++) {
        /* compute power */
        power[i] = out_real[i]*out_real[i] + out_img[i]*out_img[i];
        total_power += power[i];
        /* compute magnitude and phase */
        magnitude[i] = 2.0*sqrt(power[i]);
        phase[i] = atan2(out_img[i],out_real[i]);
    }
    /* calculate average power */
    *(avg_power) = total_power / (float) half;
}
