#Codigo que no sirve para nada
import tkinter as tk
from tkinter import ttk

#Declaramos unas funciones





#Declaramos las ventanas
ventana = tk.Tk()

#Configuramos las ventanas
ventana.title("Algo Guapo")
ventana.config(width=400, height=300)

#Ponemos un texto
texto1= ttk.Label(text="Programa que hace algo guapisimo, el que? quien sabe.")
texto1.place(x=20,y=20)

#Ponemos un boton y un entry
#entry1= ttk.Entry()
#entry1.place(x=140, y=49, width=60)

boton= ttk.Button(text="Dale loko/a")
boton.place(x=20,y=60)









ventana.mainloop()

