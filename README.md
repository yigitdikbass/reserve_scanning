# Reserve Scanning

![C++](https://img.shields.io/badge/C++-17-blue?logo=c%2B%2B)
![Graphics.h](https://img.shields.io/badge/graphics.h-BGI-lightgrey)
![cURL](https://img.shields.io/badge/libcurl-Enabled-green)
![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)

Bu proje, **çokgen tabanlı rezerv alanı tarama ve maliyet hesaplama** uygulamasıdır.  
Kullanıcıdan alınan koordinatlar ile çokgen alanı çizilir, taranır, doldurulur ve ardından sondaj/platform maliyet hesaplamaları yapılır.

---

## Özellikler
- İnternetten (HTTP) veri alma (`libcurl`)  
- Belirli bir satırdaki koordinatları okuma ve çokgen çıkarma  
- Alan hesaplama (shoelace formülü)  
- Çokgeni doldurma (`graphics.h`)  
- Piksel tarama ve kare tabanlı dolgu  
- Sondaj ve platform maliyet hesabı → kâr/zarar çıktısı  

---

## Proje Yapısı

---

## Gereksinimler
- **C++17** veya üstü  
- **graphics.h / WinBGI** (Windows ortamında)  
- **libcurl** (HTTP istekleri için)  
- Windows (WinSock2 + Windows.h bağımlılıkları nedeniyle)

---

## Derleme (Windows / MinGW örneği)
```bash
g++ main.cpp -o reserve_scanning -lcurl -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
