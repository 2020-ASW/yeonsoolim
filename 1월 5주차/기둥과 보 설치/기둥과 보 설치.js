var N;
var bo, gi;
const init = (n, build_frame) => {
    N = n;
    bo = new Array(n+1);
    gi = new Array(n+1);
    for(let i=0; i<=n; i++) {
        bo[i] = new Array(n+1);
        gi[i] = new Array(n+1);
        for(let j=0; j<=n; j++){
            bo[i][j] = false;
            gi[i][j] = false;
        }
    }
}

const giCheck = (x, y) => { // :int :int
    if(y === 0) return true;
    if(bo[y][x-1] || bo[y][x]) return true;
    if(gi[y-1][x] ) return true;
    return false;
}
const boCheck = (x, y) => {
    if(gi[y-1][x] || gi[y-1][x+1]) return true;
    if(bo[y][x-1] && bo[y][x+1]) return true;
    return false;
}
const end = () => {
    let answer = [];
    for(let i=0; i<=N; i++){
        for(let j=0; j<=N; j++){
            if(gi[j][i]){
                answer.push([i,j,0]);
            }
            if(bo[j][i]){
                answer.push([i,j,1]);
            }
        }
    }
    return answer;
}
const giRemove = (x, y) => {
    gi[y][x] = false;
    if(bo[y+1][x-1] && !boCheck(x-1,y+1)){
        gi[y][x] = true; return false;
    }
    if(bo[y+1][x] && !boCheck(x, y+1)){
        gi[y][x] = true; return false;
    }
    if(gi[y+1][x] && !giCheck(x,y+1)){
        gi[y][x] = true; return false;
    }
    return true;
}
const boRemove = (x,y) => {
    bo[y][x] = false;
    if(gi[y][x] && !giCheck(x,y)){
        bo[y][x] = true; return false;
    }
    if(gi[y][x+1] && !giCheck(x+1,y)){
        bo[y][x] = true; return false;
    }
    if(bo[y][x-1] && !boCheck(x-1,y)){
        bo[y][x] = true; return false;
    }
    if(bo[y][x+1] && !boCheck(x+1,y)){
        bo[y][x] = true; return false;
    }
    return true;
}
function solution(n, build_frame) { //build_frame => [][]
    init(n, build_frame);
    
    for(let cmd of build_frame){
        let giOrBo = cmd[2];
        let installOrRemove = cmd[3]; 
        let res;
        switch(cmd[2]){
            case 0:
                res = giCheck(cmd[0], cmd[1]);
                if(res && installOrRemove)
                    gi[cmd[1]][cmd[0]] = true;
                else if(res)
                    giRemove(cmd[0],cmd[1]);
                break;
            case 1:
                res = boCheck(cmd[0], cmd[1]);
                if(res && installOrRemove) 
                    bo[cmd[1]][cmd[0]] = true;
                else if(res)
                    boRemove(cmd[0],cmd[1]);
                break;
        }   
    }
    
    let answer = end();
    if(answer.length === 0) return [[]]
    //console.log(answer);
    return answer;
}