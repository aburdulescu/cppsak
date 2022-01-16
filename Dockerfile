FROM alpine

RUN apk update && \
    apk add git build-base clang cmake ninja python3 bash ccache && \
    ccache -M 30G

CMD sleep infinity
