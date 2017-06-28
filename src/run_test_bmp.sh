
./steganography.app -e "./default_assets/imd.bmp" "./default_assets/barney's_message.txt" "./encoded_images/suspicious_bitmap.bmp" && ./steganography.app -d "./encoded_images/suspicious_bitmap.bmp" "./decoded_secrets/suspicious_bitmap.bmp.txt"
