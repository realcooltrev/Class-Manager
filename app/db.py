import sqlite3


def connect() -> sqlite3.Connection:
    return sqlite3.connect('sis.db')
