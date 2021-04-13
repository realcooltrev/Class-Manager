import psycopg2

from . config import Config

def check_username(username: str):
    with Config.db.cursor() as cursor:
        cursor.execute("")