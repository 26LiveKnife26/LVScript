from setuptools import setup

def readme():
  with open('README.md', 'r') as f:
    return f.read()

setup(
    name = "lvscriptlvst",
    version = "1.0",
    description = "Библиотека которая представляет собой скриптовый язык, написанный на языке Python",
    long_description = readme(),
    author = "_Live___Knife_",
    author_email = "pythonisgo@gmail.com",
    url = "https://github.com/26LiveKnife26/LVScript",
    packages = "livestudioscript",
    install_requires = ["requests", "bs4", "g4f", "numpy", "flet"],
    python_requires = ">=3.11"
)