# employee-search-engine

Personel Arama ve Yönetim Sistemi

C++ ile geliştirilmiş, yüksek performanslı, konsol tabanlı bir personel yönetim ve arama motoru. Bu proje, temel veri ekleme/silme (CRUD) işlemlerinin ötesine geçerek çok hızlı isim aramaları için Trie (Ön Ek Ağacı) ve etiket tabanlı sorgular için Inverted Index (Ters İndeks) gibi gelişmiş veri yapılarını kullanmaktadır. Ayrıca gelişmiş bir puanlama sistemi ve hibrit bir öneri motoruna sahiptir.

🚀 Özellikler

👨‍💼 Yönetici (Admin) Özellikleri

Tam CRUD İşlemleri: Personel kayıtlarını sisteme ekleme, listeleme, güncelleme ve silme.

Veri Doğrulama: Sisteme eklenen her personelin benzersiz bir ID'ye ve kurumsal e-posta adresine sahip olmasını garanti eder.

Etiket Atama: Personellere uzmanlık alanlarına göre (Örn: Frontend, Backend, UI/UX, Yönetici) özel etiketler atanabilir.

👤 Kullanıcı Özellikleri

Işık Hızında İsim Arama: Kullanıcı daha ismin ilk harflerini girerken anında sonuç döndürmek için Trie (Ön Ek Ağacı) veri yapısını kullanır.

Etiket Tabanlı Arama: Tüm veritabanını taramak yerine Inverted Index kullanarak belirli yeteneklere veya rollere sahip personeli anında listeler.

Puanlama Sistemi: Kullanıcılar personellere 1 ile 5 arasında puan verebilir. Sistemdeki RatingManager, adil bir değerlendirme için aynı kullanıcının bir personele birden fazla puan vermesini engeller.

Liderlik Tablosu: Verilen puanların ortalamasını alarak "Ayın En İyi 3 Personeli"ni otomatik olarak hesaplar ve listeler.

Hibrit ML Önerisi: Arama geçmişi, personelin etiketleri ve aldığı puanlara dayanarak akıllı personel önerilerinde bulunur.

🧠 Kullanılan Temel Veri Yapıları

Trie (Ön Ek Ağacı): NameTrie.h/cpp dosyalarında uygulanmıştır. İsim aramalarında O(L) (L: aranan kelimenin uzunluğu) zaman karmaşıklığı sunarak binlerce personel arasında anında sonuç verir.

Inverted Index (Ters İndeks): Belirli etiketleri doğrudan o etikete sahip personellerin ID'leri ile eşleştirerek kategori bazlı aramaların performansını maksimize eder.

Hash Maps / Unordered Maps: RatingManager içerisinde kullanıcıların verdiği puanların kaydını tutmak, mükerrer oyları engellemek ve dinamik ortalama hesabı yapmak için yoğun olarak kullanılmıştır.

📂 Proje Yapısı

Menu.h / Menu.cpp - Konsol arayüzünü (CLI) ve kullanıcı etkileşimlerini yönetir.

NameTrie.h / NameTrie.cpp - İsim aramaları için gerekli Trie veri yapısı algoritmalarını barındırır.

RatingManager.h / RatingManager.cpp - Puanlama mantığını, veri tutarlılığını ve liderlik tablosu hesaplamalarını yönetir.

tags.txt - Personel ID'leri ve uzmanlık etiketlerinin eşleşmelerini saklayan veri dosyası.

ratings.txt - Kullanıcıların verdiği geçmiş puanları saklayan veri dosyası.

🛠️ Kurulum ve Çalıştırma

Gereksinimler

C++11 veya daha üstünü destekleyen bir C++ derleyicisi (Örn: GCC, Clang, MSVC).

Kurulum Adımları

Repoyu bilgisayarınıza klonlayın:

git clone https://github.com/kullaniciadiniz/personel-arama-sistemi.git
cd personel-arama-sistemi


Kaynak kodları derleyin:

g++ -o app main.cpp Menu.cpp NameTrie.cpp RatingManager.cpp


(Not: Derleme komutundaki dosya isimlerini projenizdeki main dosyasına göre güncelleyebilirsiniz).

Uygulamayı çalıştırın:

Windows: app.exe

Linux/macOS: ./app

🤝 Katkıda Bulunma

Projeye katkıda bulunmak, hata bildirmek veya yeni bir özellik önermek isterseniz "Issues" veya "Pull Requests" sekmelerini kullanabilirsiniz.
