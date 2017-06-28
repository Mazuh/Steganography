# Steganography
Educational experience hiding messages into images.

## More detail
Read the [requirements](./docs/proposta_ufrn_bti_itp_2017_1.pdf).

## Setting up
Let's say you're a Linux user, **c**hange **d**irectory to [./src/](./src/), and there execute:

```sh
clear && make && clear # for a clean compilation, otherwise just run 'make'
```

## Brief help
I'm assuming that you're still at **src** folder. Here's some examples of these commands...

... for hidding stuff:

```sh
# it's getting a host image and hidding a secret file on it

./steganography.app \
-e \ # stands for encode
"./default_assets/imd.ppm" \ # is the path for the image that will host the secret data
"./default_assets/heisenberg's secret.txt" \ # is the path for file that has the secret data
"./encoded_images/suspicious_portable_pixmap.ppm" \ # is the path for the resulting image file
```

... for discovering stuff:

```sh
# it's reading an image and its secrets

./steganography.app \ 
-d \ # stands for decode
"./encoded_images/suspicious_portable_pixmap.ppm" \ # is the path for the image already hosting a secret data
"./decoded_secrets/suspicious_portable_pixmap.ppm.txt" # resulting decoded filename (if you don't know what it is, just try a 'txt')
```

Note that, of course, both commands above can be done without '\' and in a single line without comments.

```sh
./steganography.app -e "./default_assets/imd.ppm" "./default_assets/heisenberg's secret.txt" "./encoded_images/suspicious_portable_pixmap.ppm"
```

```sh
./steganography.app -d "./encoded_images/suspicious_portable_pixmap.ppm" "./decoded_secrets/suspicious_portable_pixmap.ppm.txt"
```

For quick testing the routine above without copying and pasting from here, you can also run this shell script:
```sh
chmod +x ./run_test_ppm.sh
./run_test_ppm.sh
```

In case of trouble, just open an issue at [Github](https://github.com/Mazuh/Steganography)!

## Copyright
All [src](./src/) code is under this [MIT License](./LICENSE).
