import g4f
import requests
import bs4
import numpy
import datetime
import os
from random import randint, choice
from time import sleep
class Script:
    def put(self):
        print(self)
    def putf(self):
        print(f"\n{self}")
    def input(self):
        input(self)
    def inputf(self):
        input(f"\n{self}")
    def gpt(get):
        def ask_say(promt1:str)->str:
                response = g4f.ChatCompletion.create(
                model = g4f.models.gpt_35_turbo,
                messages = [{"role": "user", "content": promt1}],
    )
                return response

        os.system("clear")
        print(ask_say(get))
    gpt("Нарисуй кота")