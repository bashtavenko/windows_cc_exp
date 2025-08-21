from PIL import Image

input_jpg = "../testdata/data_matrix_9.jpg"
output_bmp = "../testdata/data_matrix_9.bmp"

try:
    # Open the image
    img = Image.open(input_jpg)

    # Convert to 8-bit grayscale.
    # 'L' mode in Pillow means 8-bit pixels, black and white.
    # This specifically creates a single-channel grayscale image.
    grayscale_img = img.convert("L")

    # Save as BMP. Pillow's 'L' mode for BMP typically results in a
    # true grayscale BMP without a palette if the underlying system supports it,
    # or a 256-entry grayscale palette if a palette is unavoidable for BMP.
    # However, 'L' mode is the closest to what you're asking for.
    grayscale_img.save(output_bmp)

    print(f"Successfully converted '{input_jpg}' to '{output_bmp}' as 8-bit grayscale.")

except FileNotFoundError:
    print(f"Error: '{input_jpg}' not found. Please ensure the file exists.")
except Exception as e:
    print(f"An error occurred: {e}")
