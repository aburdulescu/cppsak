### Start Alpine Linux container

``` shell
./run.bash
```

### Open shell into container

``` shell
docker exec -it enums_builder bash
```

### In the bash session opened into container

``` shell
cd /enums
./build.bash
```

### Stop container

``` shell
docker stop enums_builder
```

### Install

Copy `b/enums` executable somewhere in your `PATH`(e.g. `/usr/local/bin`).

``` shell
sudo cp b/enums /usr/local/bin
```
