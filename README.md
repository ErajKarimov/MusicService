# 1) Ответы на вопросы:
- Опишите самую интересную задачу в программировании, которую вам приходилось решать?
	-  Помощь другу:) Мне нужно было написать бэкенд на TypeScript. Проект состоял из  двух мобильных приложений и оба были соединены базой данных (firebase). Нужно  было решить такую задачу:```Каждый день(много владельцев) будут загружать скидки на сегодняшний день и на завтрашний. Это все должно отображаться в режиме реального времени у клиентов. Соответственно нужно было придумать структуру хранения скидок в базе данных и способ отправления, получения по дням.```   
	   TypeScript был для меня новым языком программирования. Но зная С++ мне не составило труда понять его. Реализовал  выгрузку и загрузку данных в режиме реального времени из базы данных. Владельцы загружали свои скидки и они мгновенно появлялись в клиентской части. 
							     
 - Расскажите о своем самом большом факапе? Что вы предприняли для решения проблемы?
	 - Нам нужно было показать вышеупомянутый проект. Мы все протестировали были готовы показать новые изменения и тд. Когда настал день X, мы запустили проект, было пусто, ничего не загрузилось с базы)) Время шло, а все ждут чудо). И аутентификация тоже не работала. Потом где через 20 минут я понял, что дело не в нас)) И в firebase истек срок доступа к базе. Обновил настройки и все заработало.
- Каковы ваши ожидания от участия в буткемпе?
	- Это будет полезной практикой. Ожидаю, что буду применять знания и навыки на практике. Что я буду становиться лучше с каждым днём и буду получать большое количество годной и полезной информации. И к концу буткемпа реализую большой проект.
# Разработка музыкального плейлиста
---
Проект реализован в IDE CLion на С++.

Чтобы собрать проект выполните следующие шаги:
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
./grpc-server
````
## **Пример работы:**
![Image alt](https://github.com/ErajKarimov/SberMusic/blob/master/image/Pasted%20image%2020230228224649.png)
Видео:

https://drive.google.com/file/d/1dB5g_D3Yxn1jHMq51wuOOtbyx6pH1b_H/view?usp=share_link
