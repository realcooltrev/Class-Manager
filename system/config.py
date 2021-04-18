from configparser import ConfigParser
from enum import Enum

import psycopg2


class Env(Enum):
    PROD = "prod"
    TEST = "test"


class Config():
    db: any
    environment: Env

    @classmethod
    def load(cls, environment: Env) -> None:
        cls.environment = environment

        config = ConfigParser()
        config.read(f"../config_{environment}.ini")
        cls.db = config["db"]


