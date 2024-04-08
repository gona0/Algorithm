# 12. Docker-vs-ContainerD

rkt(로켓) OCI표준을 준수했음.

Docker CRI표준을 지원하려고 만든 것은 아니다. 도커는 CRI가 나오기 전에 나와버렸어..

k8s는 임시방편인 dockershim을 도입하여 그런 도커를 지원
> - k8s 1.20부터 도커 지원 중단   
> - k8s 1.24부터 도커심 기본 지원도 중단(도커심 때문에 배포 속도가 느려지고 유지 관리자에게도 큰 부담)   
> - podman이나 cri-o나... 를 런타임으로 사용하셈   
> - 하지만 도커에서 만든 컨테이너 이미지를 등록하고 실행하는 것은 가능. 도커는 OCI와 호환되는 이미지기 때문에.   
> => 도커를 개발 도구로 계속 사용은 가능하다!

뭐 사용? CRI 인터페이스 소개 (Container Runtime Interface)
CRI는 어떤 공급업체든 쿠버네티스의 컨테이너 런타임으로 작업하게 해줌. OCI표준을 준수하는 한

OCI(Open Container Initiative) = imagespec + runtimespec
  imagespec: 이미지 빌드 방식에 대한 기준을 정의

containerD

## CLI
1. ctr: user friendly 하지 않음.
```bash
$ ctr

# image를 끌어올 수 있음
$ ctr images pull docker.io/library/redis:alpine

# 컨테이너를 실행할 수 있음
$ ctr run docker.io/library/redis:alpine redis
```

2. nerdctl: 도커와 아주 유사
```bash
$ docker
$ nerdctl

$ docker run --name redis redis:alpine
$ nerdctl run --name redis redis:alpine

$ docker run --name webserver -p 80:80 -d nginx
$ nerdctl run --name webserver -p 80:80 -d nginx
```

3. crictl(크라이컨츄롤): k8s 커뮤니티에서 개발
  별도로 설치해야함
  컨테이너 제작에 이상적으로 사용되지는 않음 - 디버깅 목적으로만 사용
  kubelet은 자기가 모르는(계획되지않은) 컨테이너들을 다 삭제함.
    컨테이너 제작을 할 필요가 없어서 디버깅만..
  https://kubernetes.io/docs/reference/tools/map-crictl-dockercli/

```bash
$ crictl 

$ crictl pull busybox
$ crictl images
$ crictl ps -a
$ crictl exec -it asdfasdfasdfasdfasdf ls
$ crictl logs asdfasdfasdf
$ crictl pods    #도커에서는 이거 안됨ㅋㅋ
```

- - -

# 13. ETCD For Beginners(엣씨디)

## What is ETCD
> ETCD is a distributed reliable key-value store that is Simple, Secure & Fast   
> 분산되고 신뢰할 수 있는 k-v스토어입니다. 단순하고 안전하며 신속하죠.   
> k-v 형식과 데이터베이스 형식 차이

## Install ETCD(2:50)
1. Download Binaries   
`$ curl -L https://github.com/etcd-io/etcd/releases/download/v3.3.11/etcd-v3.3.11-linux-amd64.tar.gz -o etcd-v3.3.11-linux-amd64.tar.gz`
3. Extract   
`$ tar zxvf etcd-v3.3.11-linux-amd64.tar.gz`
5. Run ETCD Service   
`$ ./etcd`

  default port: 2379 

## CLI
```bash
$ ./etcdctl    #help
$ ./etcdctl set key1 value1
$ ./etcdctl get key1
```

ETCDCTL Versions
  etcdctl은 2개의 api 버전을 가진다. v2와 v3를 가지는데 내가 어떤 버전을 사용하고 싶은지에 따라 version확인 필수

```bash
$ ./etcdctl --version
$ ETCDCTL_API=3 ./etcdctl version
```

- - -
# 14. ETCD in k8s

kubectl을 사용할 때 얻게 되는 모든 정보는 ETCD server에서 얻을 수 있다.   
etcd listen server 기본 port: 2379

kubeadm을 통해 설치할 수 있다.
```bash
$ kubectl get pods -n kube-system
$ kubectl exec etcd-master -n kube-system etcdctl get / --prefix -keys-only
```

etcd.service 에 다른 master node들의 정보를 넣어둬야 한다. (etcd server의 서로의 위치를 알 수 있게)


- - - 
# 16. kube-api server

primary management component in k8s(주요 관리 구성 요소)   
kube-apiserver는 클러스터에서 변경을 위해 수행해야하는 모든 작업의 중심에 있다.   
클러스터를 구성한다면 master node에서 kube-api를 다운로드하고 구성하세요.   

user -(`kubectl get nodes`)-> kube-apiserver -> ETCD CLUSTER 에서 데이터를 회수해 요청된 정보로 응답

  1. Authenticate User
  2. Validate Request
  3. Retrieve data
  4. Update ETCD
  5. Scheduler
  6. Kubelet

View api-server options - kubeadm
```bash
$ cat /etc/kubernetes/manifests/kube-apiserver.yaml
```

View api-server options
```bash
$ cat /etc/systemd/system/kube-apiserver.service
$ ps -aux | grep kube-apiserver
```


- - - 
# 17. Kube Controller Manager

k8s에서 다양한 controller를 관리   
kubectl controller manager를 설치하면 다양한 controller가 설치된다.

Node-Controller  
Watch status   
Remediate situation   
(Node-Controller -> kube-apiserver)   
아래는 설치 시 옵션
> Node Monitor Period = 5s (hb를 체크)   
> Node Monitor Grace Period = 40s   
> POD Eviction Timeout = 5m

Replication-Controller
  원하는 수의 파드가 항상 존재하도록
  
등등 Controller


- - - 
# 18. Kube Scheculer

실제로 파드를 노드에 넣는 것은 kubelet의 역할   
스케쥴러는 어떤 파드를 어디에 넣을지만 결정 (특정 기준에 따라... chart에 적어둠)   
(리소스 요구사항, 특정 응용에 적합한 노드 등)
  
  1. Filter Nodes
  2. Rank Nodes: 스케쥴러가 우선순위 함수를 통해 점수를 매김. (ex 설치 후 남은 리소스)
  
```bash
$ cat /etc/kubernetes/manifests/kube-scheduler.yaml
$ pa -aux | grep kube-scheduler 
```


- - - 
# 19. Kubelet

파드의 상태와 컨테이너를 계속 모니터링하고 kube API에 보고함   
kubeadm 은 kubelet을 자동으로 설치하지 않음   
워커노드에 수동으로 설치   

```bash
$ pa -aux | grep kubelet
```


- - -  
# 20. kube proxy

## kube proxy
Kube-proxy는 쿠버네티스 클러스터의 각 노드에서 실행되는 프로세스   
노드에서 iptables 규칙을 만들어 service IP로 트래픽을 전송

db에 접근하는 좋은 방법은 service를 이용하는 것.
  - cluster에 service를 노출
  - service는 실제가 아니라 가상임(pod같은 컨테이너가 아님)   
      - interface도 없고 listening proces도 없음   
	  - 그래서 kube proxy를 사용하는 겁니다~
 
## Installing kube-proxy
```bash
$ wget https://storage.googleapis.com/kuber....
```

## kubeadm는 각 노드에 kube-proxy pod를 배포
```bash
$ kubectl get pods -n kube-system | grep kube-proxy
$ kubectl get daemonset -n kube-system | grep kube-proxy
```


- - -
# 21. Recap - pods

## pod
k8s에서 만들 수 있는 가장 작은 단위   

사용량이 많아지면/적어지면 k8s에서 pod를 늘리든/줄이든 node를 늘리든/줄이든 한다(설정 가능)
  - pod 관련은 hpa 설정이 있어요
  - node는 모르겠음

## pod 하나에 여러 개의 container가 들어갈 수 있다.
로그 수집 container라든지, 사용자 data업로드 container라든지   
아래는 여러 컨테이너가 들어간 예시
```bash
$ kubectl get po -n test
NAME	READY	STATUS	RESTARTS	AGE
pod1	3/3 ◀	Running	0			10m
```

## pod 내부에서는 localhost 통신을 할 수 있음. 
- port로만 구분하세요   
- 저장소도 공유할 수 있음   

> pod를 쓰는 이유는 container간의 네트워크 연결을 쉽게 하기 위해서   
> 응용 프로그램 컨테이너의 상태를 모니터링   
> k8s pod는 이 모든 것을 무료로 해줍니다


## pod 배포
1. 이 명령이 실제로 하는 일은 포드를 생성해 Docker 컨테이너를 배포하는 겁니다
```bash
$ kubectl run nginx
```

2. 이미지 명시해서 지정 가능. 명시하지 않으면 Docker Hub에서 검색하는 것으로 간주
```bash
$ kubectl run nginx --image nginx
```

3. 파드 보십셔
```bash
$ kubectl get po
```


- - -
# 22. Pods with YAML

## yaml
k8s는 yaml 파일을 pods, replicas, deployments, services   
등 objects(개체) 생성을 위한 입력으로 사용

쿠버네테스 정의 파일은 항상 4개의 상위 레벨 필드를 포함합니다(필수 필드)   
apiVersion, kind, metadata, spec

## apiVersion
개체를 생성할 때 사용하는 쿠버네테스 API 버전   

|KIND      |VERSION|
|:---------|:------|
|Pod       |v1     |
|Service   |v1     |
|ReplicaSet|apps/v1|
|Deployment|apps/v1|
	
이 분야에서 가능한 값은 apps/v1beta, extensions/v1beta 등이 있는데 나중에 ㄱㄱ

##  kind
object의 종류(Pod, Service, ReplicaSet, Deployment 등)

## metadata
pod-definition.yaml
```yaml
apiVersion: v1       ─── String
kind: Pod            ─── String
metadata:            ┐
  name: myapp-pod    │
  labels:            ├── Dictionary
    app: myapp       │
  type: front-end    ┘
spec:
```

label을 통해서 리소스를 구분하고, 선택적으로 그룹화하는 방법을 제공
```bash
$ kubectl get <리소스> -l app=myapp,type=front-end
$ kubectl get pods -o wide
$ kubectl desrribe po <파드>
```

## spec
k8s로 그 object와 관련된 추가 정보를 제공   
정해진 양식이 없고 object마다 달라서 doc참조 바람   
spec은 사전 형식임

예시) pod를 만들 때, container 하나만 넣기 때문에 쉬움
```yaml
spec:
  containers:           # List/Array
    - name: nginx-container
      image: nginx      # docker 저장소에 있는 이미지
    - name: ...
```	

■ Commands
```bash
$ kubectl get po
$ kubectl desribe po myapp-pod
  # 언제 만들어졌는지
  # 어떤 라벨
  # 어떤 container들로 구성되었는지
  # 관련 events
```

- - - 
# 29. ReplicaSets
- controller: k8s의 두뇌. kubelet을 모니터링하고 그에 따라 반응하는 프로세스   
- ReplicaSets controller: k8s클러스터에 있는 단일 pod의 다중 인스턴스를 실행하도록 도와줌   
- DR: app이 down됬을 때, 다른 하나에서 응용 프로그램이 실행될 수 있다. 고가용성을 제공

## pod 고장 시 동작함
- pod가 하나뿐이어도 ReplicaSets controller는 pod(old)가 고장 났을 때 자동으로 pod(new)를 불러오게 해줌
- 특정 pod가 항상 실행되도록 보장합니다(1개든 100개든 - 개수 제한 아에 없진 않을텐데 확인 필요)

## LB & Scaling
- ResplicaSets controller는 서로 다른 node의 여러 pod에 걸쳐 부하를 분산하는 데 도움이 됨
- 수요가 증가하면 앱 스케일도 조정할 수 있음

## Replication Controller vs Replica Set
- 이미 생성된 기존의 포드를 모니터하는 데 사용할 수 있음
- Replication Controller(구식) -> Replica Set(석시딩유)
- RS가 복제를 설정하는 새로운 권장 방법
- 따라서 앞으로 모든 데모와 구현에서 RS를 사용할 예정

### Replication Controller
RC는 parent, Pod는 child

<pod-definition.yml>
```yml
apiVersion: v1
kind: Pod
metadata:
  name: myapp-pod
  labels:
    app: myapp
    type: front-end
spec:
  containers:
    - name: nginx-container
      image: nginx
```

<rc-definition.yml>
```bash
# 다른 것 처럼 4개의 섹션으로 구성
$ cat rc-definition.yml
apiVersion: v1
kind: ReplicationController
metadata:
  name: myapp-rc
  labels:
    app: myapp
	type: front-end
spec:
  # 가장 중요한 부분
  # spec.template을 만들어서 pod template을 제공하게 함
  template:
    # pod-definition.yml의 metadata와 spec 부분을 그대로 넣는다.
	
  replicas: 3
```

```bash
$ kubectl create -f rc-definition.yml
$ kubectl get replicationcontroller    # kubectl get rc?
$ kubectl get po
# 이름 prefix가 myapp-rc 인 pod가 3개 있음
```

### Replica Set
<rs-definition.yml>
```bash
$ cat rc-definition.yml
apiVersion: apps/v1    # ◀◀◀◀◀
kind: ReplicaSet    # ◀◀◀◀◀
metadata:
  name: myapp-rc
  labels:
    app: myapp
	type: front-end
spec:
  template:
    # pod-definition.yml의 metadata와 spec 부분을 그대로 넣는다.
	
  replicas: 3
  selector:       # ◀◀◀◀◀ rc와 rs의 큰 차이점. rs에서는 required. rc에서 사용 가능하지만 opt.
                  # 같은 selector를 가지고 있는 기존의 pod도 고려해서 복제함
    matchLables:
      type: front-end
      # 이거 말고 다른 옵션들도 많음. rc는 지원하지 않음.
```

```bash
$ kubectl create -f rs-definition.yml
$ kubectl get replicaset    # kubectl get rs
```


## Labels and Selectors
- Labels: rs가 어느 pod를 모니터할지 결정하게 해주는 것

## replica 개수 변경하는 법
```bash
# 1. <file>.spec.replicas = 6 변경 후
$ kubectl replace -f rs-definition.yml

# 2. 
$ kubectl scale --replicas=6 -f rs-definition.yml

# 3. 깔려있는 replicaset에서 찾기
$ kubectl scale --replicas=6 replicaset my-app-rs

# 4. 자동으로 스케일링
# hpa, 다음 기회에 
```

- - -
# 32. Deployments
$$ Replica Set \subset Deployments $$

## Rolling upgrade
- 인스턴스를 업그레이드할 때, 전부 한 번에 업그레이드할 필요는 없음
- 사용자가 우리 앱에 접속하는 데 영향을 줄 수 있으니 하나씩 업그레이드

## Definition
<deployment-definition.yml>
```yml
apiVersion: apps/v1
kind: Deployment
#밑에는 rs과 똑같
```

```
# deploy -> rs -> po
$ kubectl create -f deployment-definition.yml
$ kubectl get deployments
$ kubectl get replicaset
$ kubectl get pods
```

- 기본적으론 rs과 deployment 사이에 큰 차이는 없음
- deployment라는 resource를 만든 것 정도 차이?

- - -
# 41. Namespaces

## 개요
|namespace     |description|
|:-------------|:----------|
|default       |클러스터가 처음 설정되면 쿠버네테스가 자동으로 생성|
|kube-system   |네트워킹 솔루션, DNS 서비스, 등    |
|kube-public   |모든 사용자가 사용할 수 있는 리소스|

## Isolation
- namespace로 리소르를 분리해서 관리

## resource limit
- namespce 각각에 리소스 할당량을 할당할 수도 있음
- 할당량만 사용, 한도 초과 x

## DNS
- namespace 의 리소스도 단순히 이름으로 부를 수 있음
```bash
mysql.connect("db-service")
mysql.connect("db-service.dev.svc.cluster.local")
```

이게 가능한 이유는 서비스가 생성될 때 DNS 항목이 자동으로 이 포맷에 추가되기 때문
cluster.local: k8s cluster의 기본 도메인 이름
svc: 서비스를 위한 하위 도메인
dev: namespace
db-service: service name

## 응용
```bash
$ kubectl get pods
$ kubectl get pods --namespace=kube-system
```

```yml
$ cat pod-definitaion.yml
apiVersion: v1
kind: Pod

metadata:
  name: myapp-pod
  labels:
    app: myapp
    type: front-end
spec:
  containers:
    - name: nginx-container
      image: nginx
```

리소스 생성
```bash
$ kubectl create -f pod-definition.yml    # 기본 ns에 생성
$ kubectl create -f pod-definition.yml --namespace=dev
```

항상 같은 ns에 생성되게 하려면 `metadata.namespace: dev` 를 추가

## namespace 생성
```
$ cat namespace-dev.yml
apiVersion: v1
kind: Namespace
metadata:
  name: dev
  
$ kubectl create -f namespace-dev.yml
```

```
$ kubectl create namespace dev
```

## kube config
namespace 옵션 없이 명령어 수행하게 설정
```
$ kubectl config set-context $(kubectl config current-context) --namespace=dev
```

```
$ kubectl get pods --all-namespaces
```

## Resource Quota
```
$ cat Compute-quota.yml
apiVersion: v1
kind: ResourceQuota
metadata:
  name: compute-quota
  namespace: dev
spec:
  hard:
    pods: "10"
	requests.cpu: "4"
	requests.memory: 5Gi
	limits.cpu: "10"
	limits.memory: 10Gi
	
$ kubectl create -f compute-quota.yml
```


- - -
# 48. Kubectl Apply Command
> kubectl 명령 원리에 관해 좀 더 알아보자   
> 내부적으로 명령이 어떻게 작동하는지?

## Kubectl Apply
- 고려 대상
1. local file
2. Last applied Configuration: 마지막 응용 구성(JSON 형식)   
(라이브개체의 metadata.annotations.kubectl.kubernetes.io/last-applied-configuration)
3. kubernetes: 라이브 개체(in kubernetes memory)

- 개체가 존재하지 않으면   
=> 개체 생성

- 개체가 존재하면   
=> Live object configuration 참조

|상황              |설명|
|:-----------------|:---|
|로컬파일 값 수정  |라이브 개체값과 다르기 때문에 변경|
|로컬파일 필드 삭제|마지막 적용 구성과 비교하여 없는 걸 알아냄|

참고 링크: https://kubernetes.io/docs/tasks/manage-kubernetes-objects/declarative-config/

- 마지막으로 적용된 구성
  - 라이브 개체에 있다.
  - 이렇게 적용된 구성은 따로 저장하지 않는다.
  - (TODO)아래 명령어로 확인하는게 맞는지 확인 필요
```bash
$ kubectl get pod <개체> -oyaml | grep last-applied-configuration -A 20
```
