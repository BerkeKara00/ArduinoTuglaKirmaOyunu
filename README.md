# ARDUINO PONG OYUNU
Bu projede amaç çeşitli araçlar kullanarak mikrodenetleyici
tabanlı bir oyun makinesi geliştirmektir. Oyuncu, fiziksel
palet kontrol cihazını kullanarak bir topu hareket ettirecektir ve OLED
ekranın üst kısmında bulunan tuğlaları kırmaya calışacaktır. 


## DEVRE KURULUMU
![image](https://github.com/BerkeKara00/ArduinoTuglaKirmaOyunu/assets/105048455/7df20c21-d7dc-4994-8fbf-d7fc92ad9bbd)


## MENU EKRANI

![image](https://github.com/BerkeKara00/ArduinoTuglaKirmaOyunu/assets/105048455/2e6d7f47-7dfc-4dba-9f13-7b5f8cdcc42a)

Başlat ve Çıkış seçenekleri bulunmaktadır. Başlat seçeneğine tıklandığı takdirde oyuncu 1. seviyeden  oyuna başlayacaktır.
1.seviyede 8 tuğla ,2.seviyede 16 tuğla ,3.seviyede ise 24 tuğla bulunmaktadır. İsteğe göre seviyeler artırılabilir.
Çıkış seçeneğinde ise teşekkürler yazısı ile oyun sonlanır.   




## OYUN EKRANI GÖSTERİMİ

![image](https://github.com/BerkeKara00/ArduinoTuglaKirmaOyunu/assets/105048455/bf286c37-8244-4530-b882-788ec5840449)

Oyuncunun toplamda 3 can hakkı vardır. Bu canlar LED'ler ile gösterilmektedir. Oyuncunun bütün canları biterse oyun sonlanır ve tekrardan menü kısmına dönülür. Eğer oyuncu bölümdeki bütün tuğlaları kırarsa bir sonraki bölüme geçer. Her bölümde topun hızı artar , oyun daha da zorlaşır. Oyuncu tuğlaları kırdıkça Display ekranı üzerinde puanı artmaktadır. Ayrıca oyuncu tuğlaları kırdığı zaman %10 ihtimalle tuğladan bonus can düşer palet ile bu bonusu yakalayabilirse can kazanma hakkına sahiptir.  Oyuncu oyunu başarılı bir şekilde tamamlarsa "TEBRİKLER !" yazısı ile oyunu bitirir ve tekrardan menü kısmına dönülür.




## RENK SENSORU
![image](https://github.com/BerkeKara00/ArduinoTuglaKirmaOyunu/assets/105048455/579a1b8c-4b57-4e6a-98f9-2b899dc90da6)

Kullanıcı tercihine göre siyah ve beyaz ekran üzerinde oyunu oynayabilir
