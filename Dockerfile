# QT TCP Server (Fedora-based)
FROM fedora:36

# Install Qt5 and compiler
RUN dnf -y update && \
    dnf -y install qt5-qtbase-devel gcc-c++ make && \
    dnf clean all

# Copy project files
WORKDIR /var/lib/server
COPY . .

# Compile the project
RUN qmake-qt5 server.pro && make

# Open port
EXPOSE 65432

# Start server on container startup
CMD ["./fedora_server"]
