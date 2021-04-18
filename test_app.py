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
        self.assertTrue("name" in self.db)
        self.assertTrue("user" in self.db)
        self.assertTrue("password" in self.db)
        self.assertTrue("host" in self.db)
        self.assertTrue("port" in self.db)


class TestDb(unittest.TestCase):
    pass


if __name__ == "__main__":
    unittest.main()