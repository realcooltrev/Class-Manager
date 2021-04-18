from pathlib import Path

import pytest

from app.config import Config
from app.config import Env


@pytest.fixture
def config():
    # Need to handle sending input to stdin
    Config.load(Env.TEST)
    yield Config
    Config.reset()


@pytest.fixture
def new_config():
    mock_config_filename = f"{Path.cwd()}/mock_cfg.ini"
    Path(mock_config_filename).unlink(True)
    # Need to handle sending input to stdin
    Config.load(Env.TEST, mock_config_filename)
    yield Config
    Config.reset()


def test_load(config):
    expected_configs = [
        "name",
        "host",
        "password"
        "port",
        "user",
    ]
    assert expected_configs in config.db


def test_no_config_file(new_config):
    assert new_config.db is not None

