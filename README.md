# Steganography
Educational experience hiding messages into images.

## More detail
Read the [requirements](./docs/proposta_ufrn_bti_itp_2017_1.pdf).

## Setting up
In a Unix system, **c**hange **d**irectory to [./src/](./src/), and there, execute:

```sh
mkdir ./encoded_images/
make && ./steganography.app
```

Every time you execute the steganography program, check for this encoded_images folder.
That's where the created images (with hidden messages) will be.

## Copyright
All [src](./src/) code is under this [MIT License](./LICENSE).
