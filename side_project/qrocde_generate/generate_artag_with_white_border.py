from PIL import Image

img = Image.new("RGB", (50, 50), (255, 255, 255))
# img.save("image.png", "PNG")

artag = Image.open('artag_for_qrcode.png')



logo_pos = ((img.size[0] - artag.size[0]) // 2, (img.size[1] - artag.size[1]) // 2)

img.paste(artag, logo_pos)

img.save("artag_for_qrcode_white_border.png")