from configparser import ConfigParser
from os import environ

import psycopg2

class Config():
    db: any

    @classmethod
    def load(cls) -> None:
        config = ConfigParser()
        config.read("../config.ini")
        cls.db = config["db"]


