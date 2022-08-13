import os
from enum import (Enum, IntEnum)

PATH_BASE = os.path.dirname(os.path.realpath(__file__))
MAIL_CHECK_TIMEOUT = 60000
CLICKER_TIMEOUT = 600000


class MsgType(Enum):
    INFO: int = 1
    ERROR: int = 2
    WARNING: int = 3
    DEBUG: int = 4


class Resource(Enum):
    HEAD_HANTER: int = 1
    YANDEX: int = 2
    GOOGLE: int = 3


class ResultCode(IntEnum):
    UNDEF = 255
    ALL_RIGHT = 0
    INIT_ERROR = 1
    OPEN_FILE_ERROR = 2
    CLICKER_ERROR = 3
    NO_SUCH_ELEMENT_EXCEPTION = 4
    WEB_DRIVER_EXCEPTION = 5
    EXEC_SCRIPT_ERROR = 6
    MKDIR_ERROR = 7
