# Photon

## O projektu

**Photon** - Interaktivna GUI aplikacija za primenu vizuelnih efekata nad fotografijama.

**Članovi tima:** 

- Andrijana Čakarević ([ml14186@alas.matf.bg.ac.rs](#))
- Miloš Krsmanović ([mi15263@alas.matf.bg.ac.rs](#))
- Nebojša Koturović ([mi15139@alas.matf.bg.ac.rs](#))

<img src="https://raw.githubusercontent.com/MATF-RS20/RS009-photon/master/images/02_gui_v2.png" width="356" height="200">

**Opis projekta:**

Photon omogućava primenu nekih uobičajenih efekata nad 2D fotografijom kao što su:

- Promena osvetljenja/kontrasta
- Rotate/Flip
- Black&White, Color Invert

## Biblioteke korišćene u projektu

1) [rs_img](https://github.com/MATF-RS20/RS009-photon/tree/master/rs_img) - Biblioteka razvijena u okviru ovog projekta, namenjena da pruži korisne apstrakcije i udobnost pri radu sa fotografijama.

- Biblioteka `rs_img` se nalazi u istoimenom poddirektorijumu ovog repozitorijuma, gde možete naći detaljne instrukcije za korišćenje. Bitno je napomenuti da trenutna (interna) implementacija zavisi od **opencv** biblioteke koju je takođe potrebno imati instaliranu na sistemu.

2) [OpenCV](https://opencv.org/) - Biblioteka korišćena za manipulaciju fotografijama u okviru "zadnjeg dela" rs_img biblioteke.

3) [Qt-5](https://doc.qt.io/qt-5/) - Poznata C++ biblioteka, u ovom projektu se koristi za izradu *grafičkog korisničkog interfejsa*.

## Buildovanje projekta

Da buildujete projekat unesite sledeće shell komande:

```
cd photon
qmake && make -j8
```

U folderu `photon` će vam se pojaviti izvršni fajl koji se pokreće komandom `./Photon`.

## Eksterne reference

Razvoj projekta je otpočet još pre nego što je ovaj repozitorijum bio dodeljen našem timu, stoga vam na uvid dostavljamo reference koje prikazuju razvoj pre (ali i za vreme) razvoja projekta u okviru ovog repozitorijuma. Kao i reference na eksterne izvore (kodove) koji su korišćen u projektu.

- [Google-Drive collaboration](https://drive.google.com/drive/folders/1SgZl3qXTuc3MVdtxagyP0fmbx81U8Kl-?usp=sharing)
- [rs_img: Missing Commit History](https://github.com/nkoturovic/Programming/search?q=committer-date%3A%3E2019-11-07+author-date%3A%3C2019-11-14&unscoped_q=committer-date%3A%3E2019-11-07+author-date%3A%3C2019-11-14&type=Commits)
- [Heartbeat.fritz.ai (OpenCV)](https://heartbeat.fritz.ai/image-effects-for-android-using-opencv-cartoon-effect-9d1c8c257b2a)
- [Pimpl class (spimpl)](https://github.com/oliora/samples/blob/master/spimpl.h)
- [Generički visitor pattern](https://github.com/nkoturovic/visitor_pattern)
