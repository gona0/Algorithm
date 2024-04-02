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
```
$ ctr

# image를 끌어올 수 있음
$ ctr images pull docker.io/library/redis:alpine

# 컨테이너를 실행할 수 있음
$ ctr run docker.io/library/redis:alpine redis
```

2. nerdctl: 도커와 아주 유사
```
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

```
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

Install ETCD(2:50)
1. Download Binaries   
`$ curl -L https://github.com/etcd-io/etcd/releases/download/v3.3.11/etcd-v3.3.11-linux-amd64.tar.gz -o etcd-v3.3.11-linux-amd64.tar.gz`
3. Extract   
`$ tar zxvf etcd-v3.3.11-linux-amd64.tar.gz`
5. Run ETCD Service   
`$ ./etcd`

  default port: 2379 

CLI
```
$ ./etcdctl    #help
$ ./etcdctl set key1 value1
$ ./etcdctl get key1
```

ETCDCTL Versions
  etcdctl은 2개의 api 버전을 가진다. v2와 v3를 가지는데 내가 어떤 버전을 사용하고 싶은지에 따라 version확인 필수

```  
$ ./etcdctl --version
$ ETCDCTL_API=3 ./etcdctl version
```

- - -
# 14. ETCD in k8s

kubectl을 사용할 때 얻게 되는 모든 정보는 ETCD server에서 얻을 수 있다.   
etcd listen server 기본 port: 2379

kubeadm을 통해 설치할 수 있다.
```
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
```
$ cat /etc/kubernetes/manifests/kube-apiserver.yaml
```

View api-server options
```
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
  
```
$ cat /etc/kubernetes/manifests/kube-scheduler.yaml
$ pa -aux | grep kube-scheduler 
```


- - - 
# 19. Kubelet

파드의 상태와 컨테이너를 계속 모니터링하고 kube API에 보고함   
kubeadm 은 kubelet을 자동으로 설치하지 않음   
워커노드에 수동으로 설치   

```
$ pa -aux | grep kubelet
```
