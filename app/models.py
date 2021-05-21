from enum import Enum
from typing import Optional

from pydantic import BaseModel


class Course(BaseModel):
    id: int
    subject: str
    number: int


class Permissions(Enum):
    FACULTY = "F"
    STAFF = "A"
    STUDENT = "S"


class User(BaseModel):
    id: int
    name: str
    username: str
    password: str
