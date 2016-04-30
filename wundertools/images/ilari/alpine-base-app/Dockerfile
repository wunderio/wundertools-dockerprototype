FROM alpine

####
# Some Wundertools standards
#

# /app is our common application root
RUN mkdir /app

# create two users:
RUN /usr/sbin/addgroup -g 1000 app && \
    /usr/sbin/adduser -D -H -h /app -u 1000 -G app app && \
    /bin/chown -R app:app /app && \
    /usr/sbin/addgroup -g 500 service && \
    /usr/sbin/adduser -D -H -u 500 -G service service && \
	/usr/sbin/adduser service app
