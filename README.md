# OpenFV Samples
Sample Data for OpenFV Calibration, Refocusing, and PIV maintained by the Flow Imaging Lab at Mudd (FILM)

Assuming you already have OpenFV installed or built on your system, in order to build samples:

<pre><code>
$ git clone git@github.com:abhishekbajpayee/openfv-samples.git
$ cd openfv-samples
$ mkdir bin
$ cd bin
$ cmake [-D PYTHON_LIBS=path/to/libpython2.7.so] ..
$ make
</code></pre>
