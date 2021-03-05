# cub3D

[![jaeskim's 42 cub3D Score](https://badge42.herokuapp.com/api/project/jaeskim/cub3d)](https://github.com/JaeSeoKim/badge42)

> This project is inspired by the world-famous eponymous 90's game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you'll have to find your way.
>
> ## 📝 PDF
>
> - [**`FILE LINK`**](https://github.com/JaeSeoKim/42cursus/blob/master/pdf/en.subject-cub3D.pdf)

## 🚀 Content

### 🚩 Mandatory part

#### how to use!

##### complie!

```
make
```

##### run cub3D!

```
./cub3D map/test.cub
```

##### run cub3D with save bmp image

```
./cub3d --save map/test.cub
```

##### preview

![image-20210305195505811](image/readme/image-20210305195505811.png)



### 🚩 Bonus part

## Bonus Concept!

미로를 탈출하면서 포켓몬 구출 하기!

- 시간이 지나면 체력 ↓
- 포션을 획득시 체력 ↑
- 포켓몬을 구출시 상단 인터페이스에 출력
- 모든 포켓몬 4마리를 구출 후 출구로 도착 하면 승리!

---

#### how to use!

##### complie!

```
make bonus
```

##### run cub3D!

```
./cub3D map/level1_bonus.cub
```

##### run cub3D with save bmp image

```
./cub3d --save map/level1_bonus
```

##### preview

![cub3d_bonus_preview](image/readme/cub3d_bonus_preview.gif)

### Bonus List

- [x] Wall collisions.
- [x] A skybox.
- [x] Floor and/or ceiling texture.
- [x] An HUD.
- [x] Ability to look up and down.
- [ ] Jump or crouch.
- [x] A distance related shadow effect.
- [x] Life bar.
- [x] More items in the maze.
- [x] Object collisions.
- [x] Earning points and/or losing life by picking up objects/traps.
- [ ] Doors which can open and close.
- [ ] Secret doors.
- [x] Animations of a gun shot or animated sprite.
- [x] Several levels.
- [x] Sounds and music.
- [x] Rotate the point of view with the mouse.
