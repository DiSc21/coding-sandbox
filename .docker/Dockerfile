# FROM ubuntu:18.04
# FROM osrf/ros@sha256:ccd7251088cb37c2add84d78594aa582fac2765c0b4421b5a0bf7a534f013a86
FROM ubuntu@sha256:0fedbd5bd9fb72089c7bbca476949e10593cebed9b1fb9edf5b79dbbacddd7d6

# install basic libraries 
RUN apt-get update && apt-get install -y
RUN apt-get install -y --no-install-recommends --fix-missing ninja-build curl gcc gnupg2 wget build-essential lsb-release software-properties-common

# install cmake 
CMD mkdir /opt/cmake
WORKDIR /opt/cmake/
RUN wget --no-check-certificate https://github.com/Kitware/CMake/releases/download/v3.22.0-rc2/cmake-3.22.0-rc2-linux-x86_64.sh
RUN sh cmake-3.22.0-rc2-linux-x86_64.sh --skip-license
ENV PATH="/opt/cmake/bin/:${PATH}"

# install gtest
RUN /bin/bash -c "mkdir -p /third_party/gtest && cd /third_party/gtest && \
  tar -xvz --strip 1 -f <(wget --no-check-certificate -q -O - https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz) && \
  cmake -Bbuild -GNinja . && cmake --build build --target install && rm -rf /third_party/"

# llvm for clang format 14
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - \
&& add-apt-repository "deb http://apt.llvm.org/bionic/   llvm-toolchain-bionic  main" \
&& add-apt-repository "ppa:ubuntu-toolchain-r/test" \
&& apt-get update && apt-get install -y --no-install-recommends --fix-missing clang-format-14

# install rustc
RUN apt-get install -y --no-install-recommends --fix-missing rustc
CMD ["rustc --version"]

# install gtk3
RUN apt-get install -y --no-install-recommends --fix-missing pkg-config libgtk-3-dev libgtkmm-3.0-dev libgstreamermm-1.0-dev
RUN apt-get purge fcitx-module-dbus
ENV PKG_CONFIG_PATH="/usr/lib/x86_64-linux-gnu/pkgconfig:/usr/lib/x86_64-linux-gnu/gtkmm-3.0/include/:/usr/share/pkgconfig:${PKG_CONFIG_PATH}"

# install marp
#RUN /bin/bash -c "cd /usr/bin/ && tar -xvz -f <(wget --no-check-certificate -q -O - https://github.com/marp-team/marp-cli/releases/download/v1.4.2/marp-cli-v1.4.2-linux.tar.gz)";

CMD mkdir /ws/
WORKDIR /ws/
CMD ["echo DIRMAN SCHNELLER"]

