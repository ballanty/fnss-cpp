# Docker container for running fnss-cpp
#
# Some useful commands:
#
# Build:        docker build -t fnss-cpp .
# Open shell:   docker run -v `pwd`:/fnss-cpp --rm -it fnss-cpp
# Run command:  docker run -v `pwd`:/fnss-cpp fnss-cpp <COMMAND>
#
# For example to run all tests and build the library you may run:
# docker run -v `pwd`:/fnss-cpp --rm -it fnss-cpp make clean
#
FROM ubuntu:18.04

RUN apt-get update && apt-get install -y \
  make \
  clang \
  g++ \
  doxygen

RUN mkdir /fnss-cpp
WORKDIR /fnss-cpp

CMD ["bash"]
