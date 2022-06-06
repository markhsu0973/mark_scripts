#! /usr/bin/env python
import requests
import time

# 有货通知 收件邮箱
mail = 'xxxxx@qq.com'
# 商品的url
url = [
    'https://c0.3.cn/stock?skuId=100011293950&area=19_1607_4773_0&venderId=1000078145&buyNum=1&choseSuitSkuIds=&cat=9192,12190,1517&extraParam={%22originid%22:%221%22}&fqsp=0&pdpin=&pduid=1580214678781491106132&ch=1&callback=jQuery4173314',
    'https://c0.3.cn/stock?skuId=34424081673&area=19_1607_3639_0&venderId=656282&buyNum=1&choseSuitSkuIds=&cat=9192,12190,1517&extraParam={%22originid%22:%221%22}&fqsp=0&pdpin=&pduid=1580214678781491106132&ch=1&callback=jQuery7815511',
    'https://c0.3.cn/stock?skuId=14567560031&area=6_318_320_44149&venderId=70651&buyNum=1&choseSuitSkuIds=&cat=9847,13533,13534&extraParam={%22originid%22:%221%22}&fqsp=0&pdpin=&pduid=1580535906442142991701&ch=1&callback=jQuery660434',
    'https://c0.3.cn/stock?skuId=100011293952&area=19_1607_4773_0&venderId=1000078145&buyNum=1&choseSuitSkuIds=&cat=9192,12190,1517&extraParam={%22originid%22:%221%22}&fqsp=0&pdpin=&pduid=1580214678781491106132&ch=1&callback=jQuery5497502',
    'https://c0.3.cn/stock?skuId=11300307432&area=2_2824_51916_0&venderId=646174&buyNum=1&choseSuitSkuIds=&cat=9192,12190,1517&extraParam={%22originid%22:%221%22}&fqsp=0&pdpin=&pduid=1580214678781491106132&ch=1&callback=jQuery4188953',
]


def sendMail(url):
    import smtplib
    from email.mime.text import MIMEText
    # email 用于构建邮件内容
    from email.header import Header

    # 用于构建邮件头

    # 发信方的信息：发信邮箱，QQ 邮箱授权码
    from_addr = 'xxxxxxxx@qq.com'
    password = 'alpsneahzhawbfgj'

    # 收信方邮箱
    to_addr = mail

    # 发信服务器
    smtp_server = 'smtp.qq.com'

    # 邮箱正文内容，第一个参数为内容，第二个参数为格式(plain 为纯文本)，第三个参数为编码
    msg = MIMEText(url + ' 有口罩啦', 'plain', 'utf-8')

    # 邮件头信息
    msg['From'] = Header(from_addr)
    msg['To'] = Header(to_addr)
    msg['Subject'] = Header('有口罩啦')

    # 开启发信服务，这里使用的是加密传输
    server = smtplib.SMTP_SSL(host=smtp_server)
    server.connect(smtp_server, 465)
    # 登录发信邮箱
    server.login(from_addr, password)
    # 发送邮件
    server.sendmail(from_addr, to_addr, msg.as_string())
    # 关闭服务器
    server.quit()