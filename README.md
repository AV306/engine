# engine

2D SFML game "engine" of sorts.

<br>

## stuff

- Tile-based maps
- update() method like Unity
- Component-like things (coming soon)
- It works

<br>

## limitations

- Map tilesets can only contain a maximum of 255 tiles (about 16x16), because the map format currently only allocates 1 byte for the tile index
- Engine will crash with a segfault if a non-existent texture is loaded

<br>

## building

1. Clone the repo (I can't believe you have to explicitly tell GitHub Actions this. otherwise it just runs in an empty repo)
2. Install the dependencies through `./install_deps` (Installs Cate and SFML)
3. Run `cate` in the project root
4. Find the executable in `out/`

## running

```./out/game --asset-dir="/path/to/asset/directory/"```


<br>

## credits

- [TheMilkies/Cate](https://github.com/TheMilkies/Cate): The best C++ build system you'll ever have.
- [Darren Mulholland/Args++](http://www.dmulholl.com/docs/argspp/master/index.html): The simplest and easiest-to-use arg-parsing library out there ***by far***.
