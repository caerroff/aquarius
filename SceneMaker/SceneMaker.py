#!/bin/python3

import os
import sys
import yaml

class Action:
    def __init__(self, name, time=0):
        self.name = name
        self.time = time
        self.objects = []
        self.musicPath = ""

    def addObject(self, object):
        self.objects.append(object)

    def addMusic(self, musicPath):
        self.music = musicPath
    
    def getMusic(self):
        if(self.musicPath != ""):
            return self.musicPath
        else:
            return None

class Scene:
    def __init__(self, name, exists=False):
        self.name = name
        self.actions = []
        self.path = os.path.join(os.getcwd(),'assets/scene/' + name + '.scene')
        self.file = os.open(self.path, os.O_RDWR | os.O_CREAT)
        os.write(self.file, bytes("Scene|" + name + "\n", 'utf-8'))

class Rectangle:

    
    def __init__(self,width, height, color, centered=True, x = 0, y = 0):
        self.x = x
        self.y = y
        self.width = width
        self.height = width
        self.color = color
        self.centered = centered

    #Format : "Rectangle|Color|Centered|X|Y|Width|Height"
    def __str__(self):
        returnedString = "Rectangle|"

        returnedString += self.color + "|"
        if(self.centered):
            returnedString += "1"
        else:
            returnedString += "0|"
            returnedString += str(self.x) + "|"
            returnedString += str(self.y) + "|"
        returnedString += str(self.width) + "|"
        returnedString += str(self.height) 

        return returnedString

class Text:
    
    def __init__(self, text, r, g, b, size, centered=True, x = 0, y = 0):
        self.x = x
        self.y = y
        self.text = text
        self.colorR = r
        self.colorG = g
        self.colorB = b
        self.centered = centered

    #Format : "Text|Text|Color|Size|Centered|X|Y"
    def __str__(self):
        returnedString = "Text|"
        returnedString += self.text + "|"
        returnedString += self.colorR + "|"
        returnedString += self.colorG + "|"
        returnedString += self.colorB + "|"
        returnedString += str(self.size) + "|"
        if(self.centered):
            returnedString += "1|"
        else:
            returnedString += "0|"
            returnedString += str(self.x) + "|"
            returnedString += str(self.y) + "|"
        return returnedString


def loadScene(name):
    if os.path.exists(os.path.join(os.getcwd(),'assets/scene/' + name + '.scene')):
        print("Scene exists")
        return Scene(name)
    else:
        print("Scene does not exist")
        return Scene(name)
    
def saveScene(scene):
    print("Saving scene")
    if(action.getMusic() != None):
        os.write(scene.file, bytes("Music|" + action.getMusic() + "\n", 'utf-8'))
    for action in scene.actions:
        os.write(scene.file, bytes('Action|' + action.name + " \nTime|" + str(action.time) + "\n", 'utf-8'))
    for object in action.objects:
        os.write(scene.file, bytes(str(object) + "\n", 'utf-8'))

# Creating the prompt for the user
print("Welcome to SceneMaker!")
name = str(input("Please enter the name of the Scene you are trying to create or update (without the extension):"))
name = name.lower()
name = name.replace(" ", "")
scene = loadScene(name)
prompt = ""
while(prompt != "exit"):
    prompt = str(input("Command (type ? for the list):"))

    if(prompt == "?"):
        print("Commands:")
        print("add - Add an action to the scene")
        print("exit - Exit the program")
        print("list - List all actions in the scene")
        print("remove - Remove an action from the scene")
        print("save - Save the scene")

    if(prompt == "list"):
        if len(scene.actions) > 0:
            print("Actions:")
            print("Name | Time")
            for action in scene.actions:
                print(action.name + " | " + str(action.time) + " | " + str(action.objects))
        else:
            print("No actions in the scene")
    
    if(prompt == "add"):
        action_name = str(input("Action Name:"))
        time = int(input("Time:"))
        action = Action(action_name, time)
        answer = str(input("Would you like to add music ?(y/n):"))
        if(answer == "y"):
            music = str(input("Music path:"))
            action.addObject(music)

        answer = str(input("Would you like to add an object ?(y/n):"))
        while(answer == "y"):
            object_type = str(input("Object type (rectangle/text):"))
            if(object_type == "rectangle"):
                centered = input("Centered (y/n):")
                if(centered == "y"):
                    centered = True
                else:
                    centered = False
                    x = int(input("X:"))
                    y = int(input("Y:"))
                width = int(input("Width:"))
                height = int(input("Height:"))
                color = str(input("Color:"))
                if(centered):
                    object = Rectangle(width, height, color)
                else:
                    object = Rectangle(width, height, color, False, x, y)

                action.addObject(object)
            if(object_type == "text"):
                text = str(input("Text:"))
                r = str(input("Color R:"))
                g = str(input("Color G:"))
                b = str(input("Color B:"))
                size = int(input("Size:"))
                object = Text(text, r, g, b, size)
                action.addObject(object)
            answer = str(input("Would you like to add another object ?(y/n):"))
        scene.actions.append(action)

    if(prompt == "save"):
        saveScene(scene)
        print("Scene saved")

    if(prompt == "exit"):
        os.close(scene.file)
        break
