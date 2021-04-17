from configparser import ConfigParser
import logging
from os import environ

import psycopg2

class Config():
    db: any

    @classmethod
    def load(cls) -> None:
        logging.info("Connecting to database...")
        cls.db = psycopg2.connect(
            db_name=environ["PGDATABASE"],
            user=environ["PGUSER"],
            password=environ["PGPASSWORD"],
            host=environ["PGHOST"],
            port=environ["PGPORT"]
        )
        logging.info("Connected to database successfully")

