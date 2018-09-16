
FROM centos:latest

RUN yum -y update
RUN yum clean all && \
yum update -y && \
yum install kernel-devel -y && \
yum install compat-glibc-headers -y && \
yum groupinstall "Development Tools" -y && \
yum install epel-release -y && \
yum install glibc-headers -y && \
yum install yum-utils -y && \
yum install ImageMagick-devel -y && \
yum install openal-soft-devel -y && \
yum install autoconf -y && \
yum install git make unzip glew-devel glfw-devel portaudio portaudio-devel wget yasm-devel -y && \
yum install mlocate which -y && \
yum install cmake -y && \
yum install -y arts-devel && \
yum install -y freetype-devel && \
yum install -y freeglut-devel && \
yum install -y ImageMagick-c++-devel.x86_64 && \
yum install -y emacs && \
yum install -y screen && \
yum install -y gnuplot && \
yum install -y latex2html && \
yum install -y gsl-devel && \
yum install -y lapack-devel && \
yum install -y opencv-devel && \
yum install -y giflib-devel && \
yum install -y selinux-policy.noarch && \
yum install -y xorg-x11-apps && \
yum install -y glibc-devel.i686 && \
yum install -y libstdc++.i686 && \
yum install -y libstdc++.so.5 && \
yum install -y libstdc++.so.6 && \
yum install -y freeglut-devel.x86_64 && \
yum install -y python-devel.x86_64 && \
yum install -y libidn-devel.x86_64 && \
yum install -y e2fsprogs-devel.x86_64 && \
yum install -y ncurses-devel.i686 && \
yum install -y ncurses-devel.x86_64 && \
yum install -y zlib.i686 && \
yum install -y tcl-devel && \
yum install -y tk-devel && \
yum install -y recordmydesktop && \
yum install -y mxml-devel-2.9-1.el7.x86_64 && \
yum install -y glibc-static && \
yum install -y SDL-devel && \
yum reinstall -y libX11-devel-1.6.5-1.el7.x86_64 && \
yum reinstall -y xorg-x11-proto-devel-7.7-20.el7.noarch
RUN yum -y install centos-release-scl
RUN yum -y install llvm-toolset-7
ENTRYPOINT ["scl", "enable", "llvm-toolset-7", "bash"]