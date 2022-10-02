#!/usr/bin/env python3
import os
import subprocess
from PIL import Image, ImageDraw, ImageFont
from datetime import datetime
import qrcode


def hex2rgb(val: str) -> tuple:
    val = val[1:]
    rgb = [val[:2], val[2:4], val[4:]]
    out = []
    for col in rgb:
        out.append(int(col, 16))
    return tuple(out)


def make_wallpaper():
    prefix = "/home/m4t1/.config/dwm/cyber-wallpaper/"

    # Positions
    INFO_BOX_POS = [(8, 960), (300, 1080)]
    TEXT_POS = (INFO_BOX_POS[0][0]+8, INFO_BOX_POS[0][1] + 8)
    BORDER_OFFSET = 10
    BORDER_W = 1
    BORDER_FILL = "#00d7e4"
    FONT_FILL = "#80deeb"
    BARCODE_FILL = hex2rgb("#00d7e4")
    LOWER_BAR_OFFSET = 20

    # Date, Time, Kernel, Lst. upd
    now = datetime.now()
    cur_date = now.strftime("%d.%m.%Y")
    cur_time = now.strftime("%H:%M")
    kernel = subprocess.check_output(['uname', '-r']).decode().strip()
    user = subprocess.check_output(['echo $USER'], shell=True).decode().strip()
    time_perc = round((datetime.now() - datetime.strptime(f"{cur_date},0:0", "%d.%m.%Y,%H:%M")).total_seconds() / ( 60 * 60 * 24) * 100, 4)

    # Data
    INFO_TEXT = [
        f"date: {cur_date}",
        f"time: {cur_time} | {time_perc}%",
        f"kernel: {kernel}",
        f"user: {user}"
    ]
    BARCODE_TEXT = f"PC of {user} with {kernel} kernel version"

    # Create new image
    w_img = Image.new("RGBA", (1920, 1080), (150, 52, 200, 255))

    # Add background
    back = Image.open(f"{prefix}background.png")
    w_img.paste(back, (0, 0))

    # Make modifications
    draw = ImageDraw.Draw(w_img)
    font = ImageFont.truetype(font=f"{prefix}xirod.ttf", size=16)

    draw.text(TEXT_POS, "\n".join(INFO_TEXT), font=font, fill=FONT_FILL, spacing=12)

    # Generate barcode
    qr = qrcode.QRCode(version=None, border=0, box_size=2)
    qr.add_data(BARCODE_TEXT)
    qr.make(fit=True)
    code = qr.make_image(back_color=(255, 255, 255), fill_color=(0, 0, 0))
    bw, bh = code.size
    code = code.convert("RGBA")
    datas = code.getdata()
    newData = []
    for item in datas:
        if item[0] == 255 and item[1] == 255 and item[2] == 255:
            newData.append((255, 255, 255, 0))
        else:
            newData.append(BARCODE_FILL)
    code.putdata(newData)
    w_img.paste(code, (1920 - bw - 8, 1080 - bh - 8), code.convert("RGBA"))
    BARCODE_POS = (1920 - bw - 8, 1080 - bh - 8)

    # Add custom data border
    draw.line([(0, INFO_BOX_POS[0][1]-BORDER_OFFSET*2), (INFO_BOX_POS[1][0]//3*2+BORDER_OFFSET, INFO_BOX_POS[0][1]-BORDER_OFFSET*2)], fill=BORDER_FILL, width=BORDER_W)
    draw.line([(INFO_BOX_POS[1][0]//3*2+BORDER_OFFSET, INFO_BOX_POS[0][1]-BORDER_OFFSET*2), (INFO_BOX_POS[1][0]//3*2.2+BORDER_OFFSET, INFO_BOX_POS[0][1] - BORDER_OFFSET)], fill=BORDER_FILL, width=BORDER_W)
    draw.line([(INFO_BOX_POS[1][0]//3*2.2+BORDER_OFFSET, INFO_BOX_POS[0][1] - BORDER_OFFSET), (INFO_BOX_POS[1][0]-BORDER_OFFSET, INFO_BOX_POS[0][1] - BORDER_OFFSET)], fill=BORDER_FILL, width=BORDER_W)
    draw.line([(INFO_BOX_POS[1][0]-BORDER_OFFSET, INFO_BOX_POS[0][1] - BORDER_OFFSET), (INFO_BOX_POS[1][0]+BORDER_OFFSET, INFO_BOX_POS[0][1]+BORDER_OFFSET)], fill=BORDER_FILL, width=BORDER_W)
    draw.line([(INFO_BOX_POS[1][0]+BORDER_OFFSET, INFO_BOX_POS[0][1]+BORDER_OFFSET), (INFO_BOX_POS[1][0] + BORDER_OFFSET, INFO_BOX_POS[1][1])], fill=BORDER_FILL, width=BORDER_W)
    draw.line([(INFO_BOX_POS[1][0]+BORDER_OFFSET, INFO_BOX_POS[1][1]-LOWER_BAR_OFFSET), (BARCODE_POS[0]-BORDER_OFFSET*5, INFO_BOX_POS[1][1]-LOWER_BAR_OFFSET)], fill=BORDER_FILL, width=BORDER_W)
    draw.line([(BARCODE_POS[0]-BORDER_OFFSET*5, INFO_BOX_POS[1][1]-LOWER_BAR_OFFSET), (BARCODE_POS[0]-BORDER_OFFSET*2, BARCODE_POS[1]-BORDER_OFFSET*2)], fill=BORDER_FILL, width=BORDER_W)
    draw.line([(BARCODE_POS[0]-BORDER_OFFSET*2, BARCODE_POS[1]-BORDER_OFFSET*2), (1920, BARCODE_POS[1]-BORDER_OFFSET*2)], fill=BORDER_FILL, width=BORDER_W)
#    draw.line([(), ()], fill=BORDER_FILL, width=BORDER_W)

    # Save and apply
    w_img.save(f"{prefix}out.png")
    os.system(f"feh --bg-fill {prefix}out.png")

if __name__ == "__main__":
    make_wallpaper()

