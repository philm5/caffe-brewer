@echo off
set BOOST_ROOT=C:\libraries\boost_1_57_0
REM set BOOST_LIB_DIR=%BOOST_ROOT%\stage\lib
set HDF5_ROOT=C:\libraries\hdf5-1.8.14
set OPENBLAS_ROOT=C:\libraries\openblas
set OPENCV_ROOT=C:\libraries\opencv\build
set OPENCV_LIB_DIR=%OPENCV_ROOT%\x64\vc12\lib
set OPENCV_VERSION=2410
set PROTOBUF_ROOT=C:\libraries\protobuf-2.6.1
set PROTOC=%PROTOBUF_ROOT%\vsprojects\x64\Release\protoc.exe

IF NOT "%CAFFE_BREWER_ADDED_PATH%"=="" goto notextending
  echo Extending path!
  set PATH=%PATH%;%OPENCV_ROOT%\x64\vc12\bin;%HDF5_ROOT%\bin;%OPENBLAS_ROOT%\bin;C:\libraries\boost_1_57_0\stage\lib
  set CAFFE_BREWER_ADDED_PATH=1
  goto end
:notextending
  echo Path already extended. No update.

:end
