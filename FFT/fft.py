""" In order to draw the diagram """
import matplotlib
import matplotlib.pyplot as plt

""" In order to calculate the matrix """
import numpy as np

plt.style.use('seaborn-poster')
#%matplotlib inline

def FFT(x):
    """ This is the recursive implementation of the one-dimensional Cooley-Tukey FFT
        Original post at: https://pythonnumericalmethods.berkeley.edu/notebooks/chapter24.03-Fast-Fourier-Transform.html  """
    N = len(x)

    if N == 1:
        return x
    
    X_even = FFT(x[::2])
    X_odd = FFT(x[1::2])
    factor = np.exp(-2j * np.pi * np.arange(N) / N)
    X = np.concatenate(
        [X_even + factor[:int(N/2)] * X_odd,
        X_even + factor[int(N/2):] * X_odd]
    )
    return X

""" making new input """

sr = 128
ts = 1.0/sr
t = np.arange(0,1,ts)

freq = 1
x = 3*np.sin(2*np.pi*freq*t)

freq = 4
x += np.sin(2*np.pi*freq*t)

freq = 7
x += 0.5 * np.sin(2*np.pi*freq*t)

plt.figure(figsize=(8,6))
plt.plot(t,x,'r')
plt.ylabel("Amplitude")

plt.show()

""" FFT the diagram """
X=FFT(x)

# calculate the frequency
N = len(X)
n = np.arange(N)
T = N/sr
freq = n/T 

plt.figure(figsize = (12, 6))
plt.subplot(121)
plt.stem(freq, abs(X), 'b', \
         markerfmt=" ", basefmt="-b")
plt.xlabel('Freq (Hz)')
plt.ylabel('FFT Amplitude |X(freq)|')

# Get the one-sided specturm
n_oneside = N//2
# get the one side frequency
f_oneside = freq[:n_oneside]

# normalize the amplitude
X_oneside =X[:n_oneside]/n_oneside

plt.subplot(122)
plt.stem(f_oneside, abs(X_oneside), 'b', \
         markerfmt=" ", basefmt="-b")
plt.xlabel('Freq (Hz)')
plt.ylabel('Normalized FFT Amplitude |X(freq)|')
plt.tight_layout()
plt.show()