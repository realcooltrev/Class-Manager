from pathlib import Path

import pytest

from app.config import Config
from app.config import Env


@pytest.fixture
def config():
    Config.load(Env.TEST)


def test_load(config):
    assert "name" in Config.db
    assert "user" in Config.db
    assert "password" in Config.db
    assert "host" in Config.db
    assert "port" in Config.db


def test_no_config_file():
    mock_config_filename = f"{Path.cwd()}/mock_cfg.ini"
    Path(mock_config_filename).unlink(True)
    assert not Path(mock_config_filename).exists

    Config.load(Env.TEST, mock_config_filename)
    assert Path(mock_config_filename).exists
    assert Config.db is not None
