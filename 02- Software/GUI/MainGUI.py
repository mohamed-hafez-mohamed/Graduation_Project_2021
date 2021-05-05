from tkinter import * 
from tkinter.filedialog import askopenfilename
import pyrebase as Pyrebase
import time
from subprocess import call
from intelhex import IntelHex


##################### Fire base configuration ####################
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

##################################################################
##################################################################

path = ""
url = ""

flag = 0


def button_action() :
    global path 
    input_path.delete(0,"end")
    path = askopenfilename(initialdir=".\\",
                           filetypes =(("Text File", "*.txt"),("All Files","*.*")),
                           title = "Choose a file."
                           )
    input_path.insert(0, path)
    ih = IntelHex(path)  
    ih.tobinfile("Code.bin")
    
    
def upload () :
    global url
    global flag 
    data = db.child("NewUpdate").get()
    if data.val() == 1 : 
        status_label.configure(text = "Server is busy")
    else : 
        status_label.configure(text = "Uploading ...")
        
        # Updating header 
        crc = int (crc_value.get())
        Node_Id = int (NodeId_value.get())
        data =db.update({"App_crc" : crc})
        data =db.update({"Node_ID" : Node_Id})
        
        # Uploading file 
        x = storage.child("code.bin").put("Code.bin")
        
        f = open('hold.txt', 'w')
        f.write(x['downloadTokens'])
        f.close() 
        status_label.configure(text = "Uploaded")
        call(["python", "ParseURL.py"])



###################### GUI ####################
# create and initialize show balance window
window = Tk() 
window.geometry("550x300+200+100")
window.title("OTA ...")
window.configure(background="#4682B4" 
              ,highlightbackground="#4682B4"
              ,highlightcolor="black")
window.resizable(width = False, height = False)


for i in range(0 , 8) :
    window.columnconfigure(i,minsize='5m')

for i in range(0 , 8) :
    window.rowconfigure(i,minsize='5m')

'''
photo = PhotoImage(file = "bk.png")
back_label = Label(window ,image = photo
                      , font = 55 
                      , fg = '#FF0000'
                      , bg = '#4682B4')
back_label.grid(row = 0, column = 0, columnspan = 2 , rowspan = 4 )
'''

##################### Labels ########################
label = Label(window ,text = ".. OTA project .."
                      , font = 80 
                      , bg = "#4682B4"
                      , fg = '#0D0301'
                      )
label.grid(row = 1, column = 0 , columnspan = 7 )

label1 = Label(window ,text = "Choose file :"
                      , font = 60 
                      , bg = "#4682B4"
                      , fg = '#0D0301'
                      )
label1.grid(row = 3, column = 1 )

label2 = Label(window ,text = "Process status : "
                      , font = 40 
                      , bg = "#4682B4"
                      , fg = '#0D0301'
                      )
label2.grid(row = 7, column = 1 )

label3 = Label(window ,text = "CRC  :"
                      , font = 30 
                      , bg = "#4682B4"
                      , fg = '#0D0301'
                      )
label3.grid(row = 4, column = 1 )

label4 = Label(window ,text = "Node ID :"
                      , font = 30 
                      , bg = "#4682B4"
                      , fg = '#0D0301'
                      )
label4.grid(row = 5, column = 1 )

status_label = Label(window ,text = "IDLE"
                      , font = 40 
                      , bg = "#4682B4"
                      , fg = '#0D0301'
                      )
status_label.grid(row = 7, column = 2 )

##################### Entry ######################## 
input_path = Entry(window
                  , width = 20
                  , font = 30)
input_path.grid(row = 3, column = 2)


crc_value = Entry(window
                  , width = 15
                  , font = 20)
crc_value.grid(row = 4, column = 2, stick = W)


NodeId_value = Entry(window
                  , width = 15
                  , font = 20)
NodeId_value.grid(row = 5, column = 2 , stick = W )

##################### Buttons ########################
browes_button = Button(window , text = "Browse" 
                      , font = 20 
                      , command = button_action
                      , bd = 10
                      , bg = '#C28DD1'
                      )
browes_button.grid(row = 3, column = 4)

upload_button = Button(window , text = "Upload" 
                      , font = 30 
                      , command = upload
                      , bd = 10
                      , bg = '#C28DD1' )
upload_button.grid(row = 6, column = 0 , columnspan = 7)



mainloop()

