# LED + Bouton avec Anti-rebond — Arduino UNO

## Description

Montage Arduino permettant d'allumer et éteindre une LED avec un bouton poussoir.
Chaque appui bascule l'état de la LED (allumée → éteinte → allumée...).
Le montage intègre une gestion du **rebond mécanique** (bouncing) pour éviter les faux déclenchements.


![Montage](img/montage.jpg)
---

## Matériel nécessaire

| Composant | Quantité |
|---|---|
| Arduino UNO | 1 |
| LED rouge | 1 |
| Résistance 220Ω | 1 |
| Bouton poussoir | 1 |
| Breadboard | 1 |
| Fils de connexion | 4 |

---

## Branchement

| Composant | Broche Arduino |
|---|---|
| LED (anode +) | Pin 10 |
| LED (cathode −) → résistance 220Ω | GND |
| Bouton (patte 1) | Pin 2 |
| Bouton (patte 2) | GND |

> ⚠️ Le bouton doit être orienté correctement sur la breadboard : les deux fils doivent être sur des pattes **opposées** du bouton, pas sur des pattes déjà connectées entre elles.



## Pourquoi INPUT_PULLUP

Sans résistance externe, la pin du bouton **flotte** (valeur indéfinie) quand le bouton est relâché.
`INPUT_PULLUP` active une résistance interne à l'Arduino qui maintient la pin à `HIGH` au repos.

Conséquence : la logique est **inversée** :
- Bouton relâché → `HIGH`
- Bouton appuyé → `LOW`

---

## C'est quoi le rebond (bouncing) ?

Un bouton mécanique ne fait pas un contact net. Il "vibre" électriquement pendant ~10ms :

```
Signal réel à l'appui :

1 ────┐ ┌┐ ┌────────
      └─┘└─┘
         ↑
    faux signaux (rebonds)
```

L'Arduino étant très rapide, il détecte chaque rebond comme un appui séparé → la LED bascule plusieurs fois au lieu d'une.

### Solution : le chrono

Après un vrai appui détecté, on ignore tous les signaux pendant **200ms** le temps que les rebonds se stabilisent.

```
Appui réel   → bascule LED + démarre chrono
Rebond 1     →  5ms écoulées  → ignoré ✅
Rebond 2     → 12ms écoulées  → ignoré ✅
Vrai appui 2 → 350ms écoulées → accepté ✅
```

`millis()` mesure le temps écoulé sans bloquer le programme, contrairement à `delay()` qui gèle tout.
