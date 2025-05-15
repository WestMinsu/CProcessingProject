# Project 'Guardian Princess' 
## Directed by FrostByte Games

### Development Plan

| 마일스톤 | 주차 | 기간 | 목표 | 주요 작업 | 비고 |
|----------|------|-------|-------|------------|------|
| 개발 | 1주차 | 04-10 ~ 04-18 | 핵심 루프 구현 | - 모션 함수 구현<br>- 영웅 및 유닛 구현<br>- 유닛간 자동 전투 및 영웅 컨트롤 구현 |  |
| 개발 | 2주차 | 04-19 ~ 04-25 | 핵심 루프 구현 | - 재화 및 쿨타임 구현<br>- 유닛, 영웅, 본진 세부설계 <br>- 전투식 및 유닛 관련 변수 구현<br>- 모션 삽입, 에셋 찾기  |  |
| 개발 | 3주차 | 04-26 ~ 05-02 |핵심 루프 구현 | - 디버그 모드<br>- 유닛 및 영웅 핵심 메커니즘 제작|  |
| 개발 | 4주차 | 05-03 ~ 05-09 | 버그 수정| - 게임 메커니즘 관련 함수 개선<br> -  UI 개선|  |
| 폴리싱 및 빌드 안정화 | 5주차 | 05-10 ~ 05-15 | 최종 디버깅 & 밸런스 조정 | - 애나메이션 함수 수정 <br> = 유닛/영웅 능력치 및 적 유닛 수 조정<br> - 최종 배포용 빌드 릴리즈<br>-  |  |

### Daily Report 링크

> https://docs.google.com/spreadsheets/d/1pCMrHCH26WOuU8mww7w0ydIE9GglGSObBDwWjh3Pa0k/edit?usp=sharing

### 게임 한 줄 소개

**Guardian Princess**는 다양한 **미소녀** 유닛을 조합하고 영웅을 조작하여 전투를 벌이는 횡스크롤 디펜스 게임입니다.

### 게임 목표 / 승리 조건

- 아군 영웅 체력이 0이 되면 **패배**
- 적의 건물 체력을 0으로 만들면 **승리**

### 주요 게임 오브젝트

- 영웅 및 유닛 (공격력, 이동속도 등 각종 능력치)
  
- 강력한 스킬
  
- 유닛 생산을 위한 자원
  
- 적의 본진

### 게임 UI/UX 구성

- 영웅 정보: **체력, 공격 속도**
- 상호 작용: **버튼 클릭(유닛 생산, 영웅 이동, 스킬 사용 등)**
- 상태 표시: ** 스킬 상태, 유닛 정보, 기지 정보, 유닛 소환**

### 게임 흐름

> 유닛 생성 및 영웅 컨트롤 → 전투 → 반복

1. **아군 유닛과 적군 유닛끼리 자동으로 전투 진행**
2. 영웅이 전투에 개입가능
3. 적의 본진을 파괴하면 승리

### 플레이어 행동 / 선택 / 영향

- 유닛 구매
- 영웅 컨트롤
- 스킬

### 현재까지 구현된 내용

1. 유닛끼리의 충돌 및 전투
2. 유닛 소환 
3. 애니메이션 및 모션 구현
4. 유닛/영웅 구조
5. 적 기지 구현
6. UI
7. 승리/패배 구현
8. 스킬 구현

### 조작키 설명

A - 왼쪽으로 이동
D - 오른쪽으로 이동
마우스 클릭으로 유닛 생산 및 스킬 사용
SPACE - 영웅 공격

ESC - 메인 화면으로 나가기


### 플레이 영상

1주차 - https://drive.google.com/file/d/1AAtsDeci8MFzCPbUIcQ4WyWYta2DTFIo/view?usp=sharing

2주차 - https://drive.google.com/file/d/111jmq__4ogSYlMXFi1s_J7HyCpU1iGOT/view?usp=sharing

3,4 주차 - https://drive.google.com/file/d/1hyD0n-zGoDUt40LtgHu0T71qlW710Ith/view?usp=sharing

5주차 - https://drive.google.com/file/d/15QgNHU3bmRUKJcAqjCmctAKFba-873Xe/view?usp=drive_link
