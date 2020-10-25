import os,sys
from PIL import Image


def get_binarydata(filename):
    binary_values = []
    file = open(filename, "rb")
    data = file.read(1)
    while data !=b"":
        try:
            binary_values.append(ord(data))
        except TypeError:
            pass
        data = file.read(1)

    return binary_values


def create_greyscale_image_specific_with(dataset, output_filename, width=0):

    if(width == 0):
        size = len(dataset)

        if(size < 10240):
            width = 32
        elif (10240 <= size <= 10240):
            width = 64
        elif(10240*3 <= size <=10240*3):
            width = 128
        elif (10240 * 6 <= size <= 10240 * 6):
            width = 256
        elif (10240 * 10 <= size <= 10240 * 10):
            width = 384
        elif (10240 * 20 <= size <= 10240 * 120):
            width = 512
        elif (10240 * 3 <= size <= 10240 * 3):
            width = 768
        else:
            width = 1024

    height = int(size/width)+1

    image = Image.new('L', (width,height))

    image.putdata(dataset)

    imagename = "test.png"
    image.save(imagename)
    image.show()
    print(imagename+" Greyscale image created")


if __name__ == "__main__":
    file_full_path = '/Users/userid/Downloads/Bandizip.exe'

    path=os.path.dirname(file_full_path)
    base_name = os.path.splitext((os.path.basename(file_full_path)))[0]
    output_Filename = os.path.join(path, base_name)

    binary_data = get_binarydata(file_full_path)
    create_greyscale_image_specific_with(binary_data, output_Filename)