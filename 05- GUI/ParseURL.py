import pyrebase as Pyrebase


config = {
    "apiKey": "AIzaSyBuEWQyUXICCe7hQ8k3sb2DudpbcJTZX9I",
    "authDomain": "ota-test1.firebaseapp.com",
    "databaseURL": "https://ota-test1.firebaseio.com",
    "projectId": "ota-test1",
    "storageBucket": "ota-test1.appspot.com",
    "messagingSenderId": "615061447449",
    "appId": "1:615061447449:web:222d360d598c6fcb489b88",
    "measurementId": "G-QQX3ETQQB7"
    }
    
    
firebase = Pyrebase.initialize_app(config)
db = firebase.database()
auth = firebase.auth()
storage = firebase.storage()


f = open('hold.txt', 'r')
_str = f.read()
f.close()
url = storage.get_url(token = _str)
url = url.split('?')
url = url[0] + "code.bin?" + url[1]
db.update({"url" :url })
data =db.update({"NewUpdate" : 1})




