from selenium import webdriver
# from selenium.webdriver.firefox.options import Options
from selenium.webdriver.firefox.firefox_binary import FirefoxBinary
from selenium.common.exceptions import (NoSuchElementException)
from selenium.common.exceptions import (WebDriverException)
from global_defs import (Resource, ResultCode)
import os
import notify2


class Clicker:

    def __init__(self) -> None:
        pass

    def auto_click(self, _res_name: int, addr: str, login: str, password: str) -> int:
        """
        Автоматизация взаимодействия с элементами управления web-форм\n
        :param _res_name: Сокращенное наименование ресурса
        :return:
        """
        binary = FirefoxBinary("/usr/bin/firefox")
        # Опции
        opt = webdriver.FirefoxOptions()
        # -->> set headless mode on
        opt.add_argument("--headless")

        script_folder = os.path.dirname(os.path.realpath(__file__))

        log_path = script_folder + "/geckodriver.log"

        driver = webdriver.Firefox(firefox_binary=binary,
                                   options=opt,
                                   service_log_path=log_path)
        # Размер окна
        driver.set_window_size(1024, 768)
        # Ожидать 15 секунд
        driver.implicitly_wait(5)

        _result = ResultCode.UNDEF

        if _res_name == Resource.HEAD_HANTER:
            _result = self.hh_automate(driver, addr, login, password)
        elif _res_name == Resource.GOOGLE:
            pass
        elif _res_name == Resource.YANDEX:
            pass

        driver.close()

        return _result

    def hh_automate(self, driver, addr: str, login: str, password: str) -> int:

        try:
            driver.get(addr)
            driver.implicitly_wait(5)
            # Главное окно. Кнопка Войти
            # elem = driver.find_element_by_partial_link_text('Войти')
            elem = driver.find_element_by_xpath("/html/body/div[4]/div/"
                                                "div[2]/div/div/div/div/"
                                                "div[5]/a")
            elem.click()
            driver.implicitly_wait(5)

            # Кнопка выбора варианта входа (пароль/логин)
            elem = driver.find_element_by_xpath("/html/body/div[5]/div/"
                                                "div[3]/div[1]/div/div/div/"
                                                "div/div/"
                                                "div[1]/div[1]/div[1]/div[2]/"
                                                "div/div/form/div[4]/"
                                                "button[2]")
            elem.click()

            # Логин
            elem = driver.find_element_by_xpath("/html/body/div[5]/div/div[3]"
                                                "/div[1]/div/div/div/div/div/"
                                                "div[1]/div[1]/div[1]/div[2]"
                                                "/div/form/div[1]/"
                                                "fieldset/input")

            elem.send_keys(login)

            # пароль
            elem = driver.find_element_by_xpath("/html/body/div[5]/div/div[3]"
                                                "/div[1]/div/div/div/div/"
                                                "div/div[1]/div[1]/div[1]/"
                                                "div[2]/div/form/div[2]/"
                                                "fieldset/input")

            elem.send_keys(password)
            # Кнопка аутентификации
            elem21 = driver.find_element_by_xpath("/html/body/div[5]/"
                                                  "div/div[3]/div[1]/"
                                                  "div/div/div/div/div/"
                                                  "div[1]/div[1]/div[1]/"
                                                  "div[2]/div/form/div[4]/"
                                                  "div/button[1]")
            elem21.click()

            # Ждем 5 сек
            driver.implicitly_wait(5)
            
            try:
                elem = driver.find_element_by_class_name("event-counter_new-events")

                val = elem.text.replace("+", "")

                if (int(val) > 0):
                    notify2.init("ATS")
                    n = notify2.Notification("HeadHanter",
                                             "Имеются новые события",
                                             icon="/usr/share/icons/Mint-X/status/48/dialog-information.png")
                    n.set_timeout(2000)
                    n.show()
            except NoSuchElementException as e:
                pass

            # Мои резюме
            elem22 = driver.find_element_by_xpath("/html/body/div[4]/"
                                                  "div/div[2]/div[1]/"
                                                  "div/div/div/div[1]/a")
            elem22.click()
            # Находим все элементы с текстом - Поднять в поиске
            buttons = driver.find_elements_by_xpath('//button[text()='
                                                    '"Поднять в поиске"]')
            for btn in buttons:
                try:
                    btn.click()
                    driver.implicitly_wait(10)
                    # Кнопка во всплывающем окне
                    btn_close = driver.find_element_by_xpath("/html/body/"
                                                             "div[11]/div/"
                                                             "div[1]/div[2]/"
                                                             "div[1]/button")
                    btn_close.click()
                except NoSuchElementException as e:
                    print(str(e))
                    return int(ResultCode.NO_SUCH_ELEMENT_EXCEPTION)
                except WebDriverException as e:
                    print(str(e))
                    return int(ResultCode.WEB_DRIVER_EXCEPTION)
        except NoSuchElementException as e:
            print(str(e))
            return int(ResultCode.NO_SUCH_ELEMENT_EXCEPTION)
        except WebDriverException as e:
            print(str(e))
            return int(ResultCode.WEB_DRIVER_EXCEPTION)

        return int(ResultCode.ALL_RIGHT)

    def ya_automate(self, driver) -> int:
        try:
            driver.get("https://yandex.ru/")
            elem = driver.find_element_by_xpath("/html/body/div[1]/div[2]/"
                                                "div[2]/div/div[1]/nav/div/ul/"
                                                "li[4]/a/div[2]")
            elem.click()
        except NoSuchElementException as e:
            print(str(e))
            return int(ResultCode.NO_SUCH_ELEMENT_EXCEPTION)
        except WebDriverException as e:
            print(str(e))
            return int(ResultCode.WEB_DRIVER_EXCEPTION)

        return int(ResultCode.ALL_RIGHT)

    def check_new_events_hh(self, driver):
        elem = driver.find_element_by_class_name("event-counter event-counter_new-events")
        # print(elem.text.replace("+", ""))
        val = elem.text.replace("+", "")
        if(int(val) > 0):
            notify2.init("ATS")
            n = notify2.Notification("HeadHanter",
                                     "Имеются новые события",
                                     icon="/usr/share/icons/Mint-X/status/48/dialog-information.png")
            n.set_timeout(2000)
            n.show()
