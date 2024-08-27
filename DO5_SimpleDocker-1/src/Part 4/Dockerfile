FROM nginx:latest

USER root

COPY ./hello.c /home/hello.c
COPY ./start_point.sh /home/start_point.sh
COPY ./nginx.conf /etc/nginx/nginx.conf

RUN apt-get update && \
    apt-get install -y apt-utils && \
    apt-get upgrade -y && \
    apt-get install -y gcc spawn-fcgi libfcgi-dev;

WORKDIR /home/

ENTRYPOINT ["sh", "./start_point.sh"]











# # Use the latest version of Nginx image as the base image
# FROM nginx:latest

# # Switch to the root user to ensure necessary permissions
# USER root

# # Copy the C source file for the FastCGI application into the container's /home/ directory
# COPY ./hello.c /home/hello.c

# # Copy the shell script that will compile and start the FastCGI application into the container's /home/ directory
# COPY ./start_point.sh /home/start_point.sh

# # Copy the custom Nginx configuration file into the appropriate directory in the container, replacing the default config
# COPY ./nginx.conf /etc/nginx/nginx.conf

# # Set the working directory to /home/, so all subsequent commands are run from this directory
# WORKDIR /home/

# # Set the entry point of the container to run the start_point.sh script when the container starts
# ENTRYPOINT ["sh", "./start_point.sh"]

