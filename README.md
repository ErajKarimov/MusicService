Разработка музыкального плейлиста

✅Часть 1. Разработка основного модуля работы с плейлистом
---
Требуется разработать модуль для обеспечения работы с плейлистом. Модуль должен обладать следующими возможностями:

Play - начинает воспроизведение

Pause - приостанавливает воспроизведение

AddSong - добавляет в конец плейлиста песню

Next воспроизвести след песню

Prev воспроизвести предыдущую песню

✅Часть 2: Построение API для музыкального плейлиста
---
Реализовать сервис, который позволит управлять музыкальным плейлистом. Доступ к сервису должен осуществляться с помощью API, который имеет возможность выполнять CRUD операции с песнями в 

плейлисте, а также воспроизводить, приостанавливать, переходить к следующему и предыдущему трекам. Конфигурация может храниться в любом источнике данных, будь то файл на диске, либо база 

данных. Для удобства интеграции с сервисом может быть реализована клиентская библиотека.

✅Будет здорово, если:
---

в качестве протокола взаимодействия сервиса с клиентами будете использовать gRPC

напишите Dockerfile и docker-compose.yml

покроете проект unit-тестами

сделаете тестовый пример использования написанного сервиса


Проект реализован в IDE CLion на С++.
---
Чтобы собрать проект выполните следующие шаги:

Пару комментариев про gRPC:

Занимает на диске 3~3,5гб. Долгая сборка библиотек. Будьте готовы ждать больше 20 минут.

1. Установите gRPC:
````markdown
sudo apt-get install build-essential autoconf libtool pkg-config 
sudo apt-get install libgflags-dev libgtest-dev 
sudo apt-get install clang libc++-dev

sudo apt-get install protobuf-compiler libprotobuf-dev git

git clone --recurse-submodules -b v1.52.0 https://github.com/grpc/grpc
cd grpc
mkdir -p cmake/build
cd cmake/build
cmake ../..
make -j$(nproc)
sudo make install
sudo ldconfig
````

2. Клонируйте репозиторий и соберите проект:
````markdown  
git clone https://github.com/ErajKarimov/SberMusic.git
cd SberMusic
mkdir build
cd build
cmake ..
make
````

3. В папке build появятся два исполняемых файла grpc-server и grpc-client. 
Запустить можно следующим образом:
````markdown
./grpc-server
./grpc-client
````

![Image alt](https://github.com/ErajKarimov/SberMusic/blob/master/image/Pasted%20image%2020230228203937.png)

![Image alt](https://github.com/ErajKarimov/SberMusic/blob/master/image/Pasted%20image%2020230228204012.png)

В папке build, также будет находится исполняемый файл check. Который запускает unit тесты. 
````markdown
./check
````

Если вы поменяли playlist.proto, после сохранения изменений, выполните эти команды:
````
protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` playlist.proto
protoc -I . --cpp_out=. playlist.proto
````

Docker
---
---

Нужно чтобы в вашей системе был установлен Docker. Оставлю ссылку для установки:

[Docker](https://docs.docker.com/engine/install/)

Пару комментариев про gRPC:

Были готовые докер контейнеры, но с момента их создания прошло 5 лет. И они собраны со старыми версиями gRPC(1.10)(~1гб). Поэтому я попробовал собрать с новой версией это больше 1гб. Будьте готовы ждать больше 20 минут.

Чтобы запустить выполняем следующие команды:
````markdown
docker-compose build
````

Открываем новый терминал:
````markdown
docker-compose --file docker-compose.yml up -d server 
docker exec --interactive --tty $(docker-compose --file docker-compose.yml ps -q server) bash 
cd build
./grpc-server
````
Открываем новый терминал:
````markdown
docker-compose --file docker-compose.yml run client bash
cd build
./grpc-client
````
## **Пример работы:**
![Image alt](https://github.com/ErajKarimov/SberMusic/blob/master/image/Pasted%20image%2020230228224649.png)
Видео:

https://drive.google.com/file/d/1dB5g_D3Yxn1jHMq51wuOOtbyx6pH1b_H/view?usp=share_link
