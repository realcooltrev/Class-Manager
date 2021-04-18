import unittest

from system.config import Config
from system.config import Env


class TestApp(unittest.TestCase):
    pass


class TestConfig(unittest.TestCase):
    
    def setUp(self):
        Config.load(Env.TEST)
        self.db = Config.db

    def test_load(self):
        self.assertIn("name", self.db)
        self.assertIn("user", self.db)
        self.assertIn("password", self.db)
        self.assertIn("host", self.db)
        self.assertIn("port", self.db)


class TestDb(unittest.TestCase):
    pass


if __name__ == "__main__":
    unittest.main()