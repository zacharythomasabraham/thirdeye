from twilio.rest import Client
import requests

import socket

SERVER_ADDRESS = (HOST, PORT) = '', 8888
REQUEST_QUEUE_SIZE = 5

def handleTwilio(phoneNumber):
    account_sid = "ACfb5e162349ebbb65e76af8d7a8acbd99"
    auth_token = "eb4b567f42e85ecc2e7f860a1611a3bb"
    client = Client(account_sid, auth_token)
    client.messages.create(

    to = phoneNumber,
    #to = "+16508229872",
    from_="+12035189911",
    body = "Third Eye Alert: Temperature has exceeded the threshold!!!!",
    media_url = "http://images.clipartpanda.com/gridlock-clipart-145773-To_Start_A_Barbecue_Fire-Cartoon-1XLG_png_jpeg.png")
    call = client.calls.create(
        #to= payload["phoneNumber"],
        to= phoneNumber,
        from_="+12035189911",
        url="http://demo.twilio.com/docs/voice.xml"
    )
    print(call.sid)



def handle_request(client_connection):
    request = client_connection.recv(1024)
    rstring = bytes.decode(request)
    print("NEW REQUEST")
    print(rstring)
    if rstring != "" and rstring.find("phoneNumber") >= 0:
        query = rstring.split(' ')[1]
        phoneNumber = query.split("=")[1]
        print(query)
        handleTwilio(phoneNumber)
        http_response = b"""\
HTTP/1.1 200 OK

Hello, World!
"""
        client_connection.sendall(http_response)


def serve_forever():
    listen_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    listen_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    listen_socket.bind(SERVER_ADDRESS)
    listen_socket.listen(REQUEST_QUEUE_SIZE)
    print('Serving HTTP on port {port} ...'.format(port=PORT))

    while True:
        client_connection, client_address = listen_socket.accept()
        handle_request(client_connection)
        client_connection.close()

if __name__ == '__main__':
    serve_forever()



