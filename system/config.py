import logging
from os import environ

import psycopg2

class Config():
    db = None

    @staticmethod
    def load() -> None:
        logging.info("Connecting to database...")
        Config.db = psycopg2.connect(
            db_name=environ["PGDATABASE"],
            user=environ["PGUSER"],
            password=environ["PGPASSWORD"],
            host=environ["PGHOST"],
            port=environ["PGPORT"]
        )
        logging.info("Connected to database successfully")

