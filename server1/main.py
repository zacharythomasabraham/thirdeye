from flask import Flask
from twilio.rest import Client
app = Flask(__name__)

@app.route('/')
def hello_world():
  return 'Hello, ZachWorld!'  
         
if __name__ == '__main__':
  app.run()

def handleTwilio(phoneNumber):
    account_sid = "ACf23fd390b805f904cd7c5fcf75748151"
    auth_token = "9ab0a21004c8b9be9e69ece68081b965"
    client = Client(account_sid, auth_token)
    client.messages.create(
    to = phoneNumber,
    #to = "+16508229872",
    from_="+18175928679",
    body = "Third Eye Alert: Temperature has exceeded the threshold!!!!",
    media_url = "http://images.clipartpanda.com/gridlock-clipart-145773-To_Start_A_Barbecue_Fire-Cartoon-1XLG_png_jpeg.png")
    call = client.calls.create(
        to= phoneNumber,
        from_="+18175928679",
        url="http://demo.twilio.com/docs/voice.xml"
    )
    print(call.sid)


@app.route('/alert/<phoneNumber>/<currentTemperature>')
def handle_request(phoneNumber,currentTemperature):
        handleTwilio(phoneNumber)
        http_response = b"""\
HTTP/1.1 200 OK
Sending alerts
"""
        return http_response

