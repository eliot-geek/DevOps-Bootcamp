FROM nginx:latest

USER root

WORKDIR /home/

COPY ./hello.c /home/hello.c

COPY ./nginx.conf /etc/nginx/nginx.conf

RUN apt-get update && \
    apt-get -y install -y gcc libfcgi-dev spawn-fcgi; \
    gcc -o /home/hello /home/hello.c -lfcgi; \
    apt-get clean && rm -rf /var/lib/apt/lists/*; \
    curl -O https://nginx.org/keys/nginx_signing.key; \
    rpm --import ./nginx_signing.key; \
    apt-get clean && rm -rf /var/lib/apt/lists/*; \
    
    # This is to fix a fatal vulnerability
    useradd atruskat; \
    chown -R atruskat:atruskat /home; \
    chown -R atruskat:atruskat /etc/nginx/nginx.conf; \
    
    # Assigning permissions to fix INFO vulnerabilities
    chown -R atruskat:daemon /var/cache/nginx; \
    touch /var/run/nginx.pid; \
    chown -R atruskat:daemon /var/run/nginx.pid; \
    chmod g-s /usr/bin/expiry; \
    chmod u-s /usr/bin/newgrp; \
    chmod g-s /usr/bin/chage; \
    chmod g-s /sbin/unix_chkpwd; \
    chmod u-s /bin/mount; \
    chmod g-s /usr/bin/wall; \
    chmod u-s /bin/su; \
    chmod u-s /usr/bin/passwd; \
    chmod u-s /usr/bin/chfn; \
    chmod u-s /usr/bin/chsh; \
    chmod u-s /usr/bin/gpasswd; \
    chmod u-s /bin/umount;
USER atruskat

# Creating a non-root user to fix WARN vulnerability
HEALTHCHECK --interval=5m --timeout=3s CMD curl -f http://localhost/ || exit 1

# To fix INFO vulnerability
CMD ["/bin/bash", "-c", "nginx -g 'daemon off;' | nginx -s reload | spawn-fcgi -p 8080 -n /home/hello"]