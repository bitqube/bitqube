FROM amd64/ubuntu:20.04 AS base

#If you found this docker image helpful please donate BTQ to the maintainer
LABEL maintainer="RV9zdNeUTQUToZUcRp9uNF8gwH5LzDFtan"

EXPOSE 8766/tcp
EXPOSE 8767/tcp

ENV DEBIAN_FRONTEND=noninteractive

#Install runtime dependencies
RUN apt-get update && \
	apt-get install -y --no-install-recommends \
	bash wget net-tools libminiupnpc17 \
	libevent-2.1 libevent-pthreads-2.1 \
	libboost-system1.71 libboost-filesystem1.71 libboost-chrono1.71 \
	libboost-program-options1.71 libboost-thread1.71 \
	libzmq5 && \
	apt-get clean

FROM base AS build

#Install build dependencies
RUN apt-get update && \
	apt-get install -y --no-install-recommends \
	bash net-tools build-essential libtool autotools-dev automake \
	pkg-config libssl-dev libevent-dev bsdmainutils python3 \
	libboost-system1.71-dev libboost-filesystem1.71-dev libboost-chrono1.71-dev \
	libboost-program-options1.71-dev libboost-test1.71-dev libboost-thread1.71-dev \
	libzmq3-dev libminiupnpc-dev && \
	apt-get clean

#Copy source dir
COPY . /home/bitqube/build/BitQube/
WORKDIR /home/bitqube/build/BitQube

#build db4 from source
WORKDIR /home/bitqube/build/BitQube/contrib
RUN ./install_db4.sh ../../

# build BitQubecore
WORKDIR /home/bitqube/build/BitQube
RUN ./autogen.sh && ./configure --disable-tests BDB_LIBS="-L/home/bitqube/build/db4/lib -ldb_cxx-4.8" BDB_CFLAGS="-I/home/bitqube/build/db4/include" --with-gui=no  && make -j4

FROM base AS final

#Add our service account user
RUN useradd -ms /bin/bash bitqube && \
	mkdir /var/lib/bitqube && \
	chown bitqube:bitqube /var/lib/bitqube && \
	ln -s /var/lib/bitqube /home/bitqube/.bitqube && \
	chown -h bitqube:bitqube /home/bitqube/.bitqube

VOLUME /var/lib/bitqube

#Copy the compiled binaries from the build
COPY --from=build /home/bitqube/build/BitQube/src/bitqubed /usr/local/bin/bitqubed
COPY --from=build /home/bitqube/build/BitQube/src/bitqube-cli /usr/local/bin/bitqube-cli

WORKDIR /home/bitqube
USER bitqube

CMD /usr/local/bin/bitqubed -datadir=/var/lib/bitqube -printtoconsole -onlynet=ipv4
