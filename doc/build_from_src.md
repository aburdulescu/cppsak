### Start Alpine Linux container

``` shell
./run.bash
```

### Open shell into container

``` shell
docker exec -it cppsak_builder bash
```

### In the bash session opened into container

``` shell
cd /cppsak
./build.bash
```

### Stop container

``` shell
docker stop cppsak_builder
```

### Install

Copy `b/cppsak` executable somewhere in your `PATH`(e.g. `/usr/local/bin`).

``` shell
sudo cp b/cppsak /usr/local/bin
```
