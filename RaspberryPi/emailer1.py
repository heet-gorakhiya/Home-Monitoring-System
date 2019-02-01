import os
import smtplib
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart




def SendMail(ImgFileName):
    img_data = open(ImgFileName, 'rb').read()
    msg = MIMEMultipart()
    msg['Subject'] = 'Intruder'
    msg['From'] = 'tempt919@gmail.com'
    msg['To'] = 'neelsshuklaa@gmail.com'

    text = MIMEText("test")
    msg.attach(text)
    image = MIMEImage(img_data, name=os.path.basename(ImgFileName))
    msg.attach(image)

    s = smtplib.SMTP('smtp.gmail.com', 587)
    s.ehlo()
    s.starttls()
    s.ehlo()
    s.login("tempt919@gmail.com","qazwsxedcrfv123456")
    s.sendmail("tempt919@gmail.com", "neelsshuklaa@gmail.com", msg.as_string())
    s.quit()

SendMail("1.PNG")